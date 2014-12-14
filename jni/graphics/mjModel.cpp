#include "mjModel.h"

namespace mjEngine{

mjModel::mjModel()
{
	numVertices = -1;
	currentVertex = -1;
	currentFace = -1;
	faceCount = -1;
	status[0] = '\0';

}
void mjModel::LoadFromFile(const char* fileName)
{
	XMLDocument doc;

	doc.LoadFile(fileName);
	Load(&doc);
}

void mjModel::Load(XMLDocument* doc)
{


	// Doc needs to already have been parsed or loaded by this line

	XMLElement* mesh = doc->FirstChildElement();
	if (mesh != NULL)
	{
	XMLElement* sharedGeometry = mesh->FirstChildElement("sharedgeometry");
	sharedGeometry->QueryIntAttribute("vertexcount", &numVertices);


	int posIn3Array = 0;
	int posIn2Array = 0;
	vertexBuffer = new float[3*numVertices];
	normalComponentBuffer = new float[3*numVertices];
	texCoordBuffer = new float[2*numVertices];

	XMLElement* vertexbuffer = sharedGeometry->FirstChildElement("vertexbuffer");


	XMLElement* vertex = vertexbuffer->FirstChildElement("vertex");
	snprintf(status,1024, "%s", "About to go into vertex data");
	while(vertex)
	{

		XMLElement* vertexData;
		vertexData = vertex->FirstChildElement("position");
		vertexData->QueryFloatAttribute("x", &vertexBuffer[posIn3Array]);
		vertexData->QueryFloatAttribute("y", &vertexBuffer[posIn3Array+1]);
		vertexData->QueryFloatAttribute("z", &vertexBuffer[posIn3Array+2]);

		for (unsigned l = 0; l < 3; l++)
		{
            if (vertexBuffer[posIn3Array + l] < bounds[0 + l])
            {
                bounds[0 + l] = vertexBuffer[posIn3Array + l];
            }

            if (vertexBuffer[posIn3Array + l] > bounds[3 + l])
            {
                bounds[3 + l] = vertexBuffer[posIn3Array + l];
            }
		}


		vertexData = vertex->FirstChildElement("normal");
		vertexData->QueryFloatAttribute("x", &normalComponentBuffer[posIn3Array]);
		vertexData->QueryFloatAttribute("y", &normalComponentBuffer[posIn3Array+1]);
		vertexData->QueryFloatAttribute("z", &normalComponentBuffer[posIn3Array+2]);

		vertexData = vertex->FirstChildElement("texcoord");
		vertexData->QueryFloatAttribute("u", &texCoordBuffer[posIn2Array]);
		vertexData->QueryFloatAttribute("v", &texCoordBuffer[posIn2Array+1]);


		posIn3Array += 3;
		posIn2Array += 2;
		vertex = vertex->NextSiblingElement("vertex");
	}

	char tmp[1024];

	for (int i = 0; i < numVertices; i++)
	{
		snprintf(tmp, 1024, "%s\n%3.3f %3.3f %3.3f", status, vertexBuffer[3*i], vertexBuffer[(3*i)+1], vertexBuffer[(3*i)+2]);
		snprintf(status, 1024, "%s", tmp);
	}

	XMLElement* submeshes = mesh->FirstChildElement("submeshes");

	XMLElement* submesh = submeshes->FirstChildElement("submesh");
	int currentMesh = 0;
	while(submesh)
	{
		mjModelMesh* modelMesh = new mjModelMesh();

		const char* shader = submesh->Attribute("shader");
		if (shader != NULL)
		{
			int length = strnlen(shader, MJMODEL_MAXATTRSIZE)+1;
			modelMesh->shaderName = new char[length];
			strncpy(modelMesh->shaderName, shader, length);

		} else
		{
			modelMesh->shaderName = NULL;

		}

		const char* tempStrAttr = submesh->Attribute("material");
		{
			int length = strnlen(tempStrAttr, MJMODEL_MAXATTRSIZE)+1;
			modelMesh->material = new char[length];
			strncpy(modelMesh->material, tempStrAttr, length);
		}

		XMLElement* faces = submesh->FirstChildElement("faces");


		faces->QueryIntAttribute("count", &faceCount);

		modelMesh->drawOrderCount = faceCount*3;

		modelMesh-> drawOrderBuffer = new unsigned short[faceCount*3];

		int posInFaceArray = 0;
		XMLElement* face = faces->FirstChildElement("face");
		int numFacesParsed = 0;

		while(face && (numFacesParsed <= faceCount))
		{
			int attr;
			face->QueryIntAttribute("v1", &attr);
			modelMesh->drawOrderBuffer[posInFaceArray] = (unsigned short) attr;
			face->QueryIntAttribute("v2", &attr);
			modelMesh->drawOrderBuffer[posInFaceArray+1] = (unsigned short) attr;
			face->QueryIntAttribute("v3", &attr);
			modelMesh->drawOrderBuffer[posInFaceArray+2] = (unsigned short) attr;

			posInFaceArray += 3;
			numFacesParsed++;
			face = face->NextSiblingElement("face");
		}
		modelMesh->meshNumber = currentMesh;
		meshes.push_back(modelMesh);
		currentMesh++;
		submesh= submesh->NextSiblingElement("submesh");
	}

	snprintf(tmp, 1024, "%s\nParsed %d faces & %d meshes", status, faceCount, meshes.size());
	snprintf(status, 1024, "%s", tmp);


	XMLElement* submeshnames = mesh->FirstChildElement("submeshnames");

	submesh = submeshnames->FirstChildElement("submesh");
	int numSubMeshNames = 0;
	while(submesh)
	{
		int desiredIndex;
		submesh->QueryIntAttribute("index", &desiredIndex);

		{

			const char* tempStrAttr = submesh->Attribute("name");
			int length = strnlen(tempStrAttr, 96)+1;
			char* newStr = new char[length];

			strncpy(newStr, tempStrAttr, length);

			meshes[desiredIndex]->name = newStr;

		}
		numSubMeshNames++;
		submesh = submesh->NextSiblingElement("submesh");
	}

	snprintf(tmp, 1024, "%s\nParsed %d submeshnames", status, numSubMeshNames);
		snprintf(status, 1024, "%s", tmp);




	}
	else
	{
		snprintf(status, 1024, "%s", "Error: mesh == null >_<*");
	}
}

void mjModel::TieShaders(std::vector<mjShader*>& shaderList)
{

	for(unsigned i = 0; i < meshes.size(); i++)
	{
		if (meshes[i]->shaderName == NULL)
		{
			LOGI("Mesh %s: Default shader attached", meshes[i]->name);
			meshes[i]->mjShaderListIndex = 0; // 0 will always be the default shader.
		} else
		{
			for (unsigned j = 0; j < shaderList.size(); j++)
			{
				//LOGI("Considering shader %s", shaderList[j]->name);
				if (strncmp(meshes[i]->shaderName, shaderList[j]->name, 96) == 0)
				{
					LOGI("Mesh %s: %s shader attached",meshes[i]->name, shaderList[j]->name);
					meshes[i]->mjShaderListIndex = j;
				}
			}
			if (meshes[i]->mjShaderListIndex == 0)
			{
				LOGI("Mesh %s: %s shader not found", meshes[i]->name, meshes[i]->shaderName);
			}
		}
	}
}

void mjModel::Draw(std::vector<mjShader*>& shaderList,
		float* modelMatrix, float* lookAtMatrix, float* modelViewMatrix, float* projectionMatrix, float* modelViewProjectionMatrix, mjModelPose* pose)
{
    float poseMatrix[16];
    float tempMatrix[16];
    float* whichMatrix;
	//Matrix4::DebugM("mvp", modelViewProjectionMatrix);





	for(unsigned i = 0; i < meshes.size(); i++)
	{
	    if (pose)
        {


            mjVector3 testPos(0,0,0);


            Matrix4::GetPositionScaleAndAngleRotationMatrix(testPos, *pose->angles[i], poseMatrix);//(*pose->positions[i], *pose->angles[i], poseMatrix);
            Matrix4::MultiplyMM(tempMatrix, 0,
                                modelMatrix, 0,
                                poseMatrix, 0);

            Matrix4::MultiplyMM(modelViewMatrix, 0,
			lookAtMatrix, 0,
			tempMatrix, 0);
            //Matrix4::MultiplyMM(modelViewMatrix, 0, )
        } else
        {
            Matrix4::MultiplyMM(modelViewMatrix, 0,
			lookAtMatrix, 0,
			modelMatrix, 0);
        }
        Matrix4::MultiplyMM(modelViewProjectionMatrix, 0,
						projectionMatrix, 0,
						modelViewMatrix, 0);

		shaderList[meshes[i]->mjShaderListIndex]->Run(meshes[i],
				vertexBuffer, texCoordBuffer, normalComponentBuffer,
				modelMatrix, modelViewProjectionMatrix);

		glDrawElements(GL_TRIANGLES, meshes[i]->drawOrderCount, GL_UNSIGNED_SHORT, meshes[i]->drawOrderBuffer);
	}
}

mjModelPose* mjModel::CreateSimplePose()
{
    mjModelPose* pose = new mjModelPose();
    for (unsigned i = 0; i < meshes.size(); i++)
    {
        pose->angles.push_back(new mjVector3());
        pose->positions.push_back(new mjVector3());
    }
    return pose;
}

}// namespace mj
