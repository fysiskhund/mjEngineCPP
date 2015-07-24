#include "mjModel.h"

namespace mjEngine{

mjModel::mjModel()
{
	numVertices = -1;
	currentVertex = -1;
	currentFace = -1;
	faceCount = -1;
	status[0] = '\0';

#ifdef OSX
    // Generate the buffers needed for CORE profile compliance
    glGenVertexArraysAPPLE(1, &vertexArrayObject);
    glGenBuffers(3, objectBuffers);
#endif


}
void mjModel::LoadFromFile(const char* fileName)
{
    tinyxml2::XMLDocument doc;

	doc.LoadFile(fileName);
	Load(&doc);
}

void mjModel::Load(tinyxml2::XMLDocument* doc)
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
	snprintf(status, 1024, "%s", "About to go into vertex data");
	while(vertex)
	{

        // Read the vertices' components
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

        // Read normal components
		vertexData = vertex->FirstChildElement("normal");
		vertexData->QueryFloatAttribute("x", &normalComponentBuffer[posIn3Array]);
		vertexData->QueryFloatAttribute("y", &normalComponentBuffer[posIn3Array+1]);
		vertexData->QueryFloatAttribute("z", &normalComponentBuffer[posIn3Array+2]);

        // Read texture coordinates
		vertexData = vertex->FirstChildElement("texcoord");
		vertexData->QueryFloatAttribute("u", &texCoordBuffer[posIn2Array]);
		vertexData->QueryFloatAttribute("v", &texCoordBuffer[posIn2Array+1]);


		posIn3Array += 3;
		posIn2Array += 2;
		vertex = vertex->NextSiblingElement("vertex");
	}


#ifdef OSX
    glBindVertexArrayAPPLE(vertexArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, objectBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(GLfloat)*3, vertexBuffer, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, objectBuffers[1]);
    glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(GLfloat)*3, normalComponentBuffer, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, objectBuffers[2]);
    glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(GLfloat)*2, texCoordBuffer, GL_STATIC_DRAW);
#endif


    /* debug stuff
	char tmp[1024];

	for (int i = 0; i < numVertices; i++)
	{
		snprintf(tmp, 1024, "%s\n%3.3f %3.3f %3.3f", status, vertexBuffer[3*i], vertexBuffer[(3*i)+1], vertexBuffer[(3*i)+2]);
		snprintf(status, 1024, "%s", tmp);
	}*/

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

		modelMesh->drawOrderBuffer = new unsigned short[faceCount*3];

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

//	snprintf(tmp, 1024, "%s\nParsed %d faces & %d meshes", status, faceCount, meshes.size());
//	snprintf(status, 1024, "%s", tmp);


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

//	snprintf(tmp, 1024, "%s\nParsed %d submeshnames", status, numSubMeshNames);
//		snprintf(status, 1024, "%s", tmp);




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
			//LOGI("Mesh %s: Default shader attached", meshes[i]->name);
			meshes[i]->mjShaderListIndex = 0; // 0 will always be the default shader.
		} else
		{
			for (unsigned j = 0; j < shaderList.size(); j++)
			{
				//LOGI("Considering shader %s", shaderList[j]->name);
				if (strncmp(meshes[i]->shaderName, shaderList[j]->name, 96) == 0)
				{
					//LOGI("Mesh %s: %s shader attached",meshes[i]->name, shaderList[j]->name);
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

void mjModel::TieStructureToMeshes() // Attaches the nodes to the proper meshes
{
    if (structure)
    {
        for (unsigned i = 0; i < structure->nodes.size(); i++)
        {
            for (unsigned j = 0; j < this->meshes.size(); j++)
            {
                if (strncmp(structure->nodes[i]->meshName.c_str(), this->meshes[j]->name, 128) == 0)
                {
                    structure->nodes[i]->meshIndex = j;
                }
            }
        }
    }
}
void mjModel::TiePoseToStructure()
{
/*    if (pose && structure)
    {
        for (unsigned i = 0; i < structure->nodes.size(); i++)
        {
            for (unsigned j = 0; j < pose->nodes.size(); j++)
            {
                if (strncmp(structure->nodes[i]->meshName.c_str(), pose->meshes[j]->name, 128) == 0)
                {
                    structure->nodes[i]->meshIndex = j;
                }
            }
        }
    }*/
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

#if defined(USE_GLES2) || defined(USE_GL3)
// Drawing routine for OpenGL ES 2.0 & OpenGL 3

void mjModel::Draw(std::vector<mjShader*>& shaderList,
		float* modelMatrix, float* lookAtMatrix, float* modelViewMatrix, float* projectionMatrix, float* modelViewProjectionMatrix, mjModelPose* pose)
{
    float poseMatrix[16];
    float tempMatrix[16];
    float matrixAfterStack[16];
    float* whichMatrix;



	//Matrix4::DebugM("mvp", modelViewProjectionMatrix);




    if (0)//structure)
    {
        mStack.PopAll();
        Matrix4::SetIdentityM(mStack.current, 0);
        int debugVar = structure->nodes.size();
        printf("dbvar: %d\n", debugVar);
    	for (unsigned i = 0; i < structure->nodes.size(); i++)
    	{

            std::string debugVar = structure->nodes[i]->meshName;
            printf("dbvar: %s\n", debugVar.c_str());
            //Perform the stack operation
    		switch(structure->nodes[i]->operation)
    		{
    		case MJ_NODE_NOOP:
    			//Nothing.
    			break;
    		case MJ_NODE_PUSH:
    			mStack.Push(tempMatrix);
    			break;
    		case MJ_NODE_POP:
    			mStack.Pop();
    			break;
    		case MJ_NODE_RESET:
    			mStack.PopAll();
    			break;
    		}

    		// Get the particular mesh we're operating on in this node of the structure
            unsigned meshNum = structure->nodes[i]->meshIndex;


    		mjVector3 positions;

    		// Get the positions from the pose. Add them as displacement from the base position for this structure node
    		positions.CopyFrom(structure->nodes[i]->meshPos);
    		positions.Add(*pose->positions[i]); // pose MUST coincide with modelStructure since one model might use the same mesh in several places, each with its own pose

            // Get the angles for the pose for this particular structure node.
            // I think I decided not to have any other angle than 0 as base in the structure; therefore no summing angles
    		mjVector3 angles;
    		angles.CopyFrom(*pose->angles[meshNum]);

    		Matrix4::GetPositionScaleAndAngleRotationMatrix(positions, angles, poseMatrix);//(*pose->positions[i], *pose->angles[i], poseMatrix);
            Matrix4::MultiplyMM(tempMatrix, 0,
    					modelMatrix, 0,
						poseMatrix, 0);

            Matrix4::MultiplyMM(modelViewMatrix, 0,
    					lookAtMatrix, 0,
						tempMatrix, 0);

            Matrix4::MultiplyMM(modelViewProjectionMatrix, 0,
    				projectionMatrix, 0,
					modelViewMatrix, 0);

    		shaderList[meshes[i]->mjShaderListIndex]->Run(meshes[i],
    				vertexBuffer, texCoordBuffer, normalComponentBuffer,
					modelMatrix, modelViewProjectionMatrix);

    		/*

    		Matrix4::GetPositionScaleAndAngleRotationMatrix(positions,
    				angles,
					poseMatrix);//(*pose->positions[i], *pose->angles[i], poseMatrix);

    		Matrix4::MultiplyMM(tempMatrix, 0,
    				modelMatrix, 0,
					poseMatrix, 0);

    		Matrix4::MultiplyMM(matrixAfterStack, 0,
    		    				tempMatrix, 0,
    							mStack.current, 0);

    		Matrix4::MultiplyMM(modelViewMatrix, 0,
    				lookAtMatrix, 0,
					matrixAfterStack, 0);





    		shaderList[meshes[meshNum]->mjShaderListIndex]->Run(meshes[meshNum],
    				vertexBuffer, texCoordBuffer, normalComponentBuffer,
					modelMatrix, modelViewProjectionMatrix);
					*/

    		glDrawElements(GL_TRIANGLES, meshes[meshNum]->drawOrderCount, GL_UNSIGNED_SHORT, meshes[meshNum]->drawOrderBuffer);
    	}
    } else
    {
    	for(unsigned i = 0; i < meshes.size(); i++)
    	{
    		if (pose)
    		{


    			mjVector3 testPos;
    			mjVector3 angles;
    			angles.CopyFrom(*pose->angles[i]);
    			testPos.CopyFrom(*pose->positions[i]);

    			Matrix4::GetPositionScaleAndAngleRotationMatrix(testPos, angles, poseMatrix);//(*pose->positions[i], *pose->angles[i], poseMatrix);
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
}

#elif USE_NULL_RENDERER
void mjModel::Draw(std::vector<mjShader*>& shaderList,
	float* modelMatrix, float* lookAtMatrix, float* modelViewMatrix, float* projectionMatrix, float* modelViewProjectionMatrix, mjModelPose* pose)
{
	// Nothing is rendered, this is useful for the dedicated-server version of the games
}
#else
    #error "No rendering system is defined. Choose USE_GLES2, USE_GL3 or USE_NULL_RENDERER"
#endif

}// namespace mj
