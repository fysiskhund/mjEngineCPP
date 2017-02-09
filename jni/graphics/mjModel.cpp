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
    LOGI("Loading model from file %s", fileName);
    tinyxml2::XMLDocument doc;

	doc.LoadFile(fileName);
    Load(&doc);
}

void mjModel::LoadFromMemory(const unsigned char* buffer, size_t totalLength)
{
    LOGI("Loading model from buffer; %d bytes",totalLength);
    tinyxml2::XMLDocument doc;
    doc.Parse((const char*) buffer, totalLength);
    Load(&doc);
}

void mjModel::Load(tinyxml2::XMLDocument* doc)
{

   checkGlError("first line of model load");
	// Doc needs to already have been parsed or loaded by this line

	XMLElement* mesh = doc->FirstChildElement();
	if (mesh != NULL)
	{
	XMLElement* sharedGeometry = mesh->FirstChildElement("sharedgeometry");
	sharedGeometry->QueryIntAttribute("vertexcount", &numVertices);


	int posIn3Array = 0;
	int posIn2Array = 0;
    vertexBufferData = new float[3*numVertices];
    LOGI("%s %d: new %s [3*%d]", __FILE__, __LINE__, "float for vertexData", numVertices);

    normalComponentBufferData = new float[3*numVertices];
    LOGI("%s %d: new %s [3*%d]", __FILE__, __LINE__, "float for normalData", numVertices);

    texCoordBufferData = new float[2*numVertices];
    LOGI("%s %d: new %s [3*%d]", __FILE__, __LINE__, "float for texcoords",  numVertices);


	XMLElement* vertexbuffer = sharedGeometry->FirstChildElement("vertexbuffer");


	XMLElement* vertex = vertexbuffer->FirstChildElement("vertex");
	snprintf(status, 1024, "%s", "About to go into vertex data");
	while(vertex)
	{

        // Read the vertices' components
		XMLElement* vertexData;
		vertexData = vertex->FirstChildElement("position");
        vertexData->QueryFloatAttribute("x", &vertexBufferData[posIn3Array]);
        vertexData->QueryFloatAttribute("y", &vertexBufferData[posIn3Array+1]);
        vertexData->QueryFloatAttribute("z", &vertexBufferData[posIn3Array+2]);

        // Determine bounds of object
		for (unsigned l = 0; l < 3; l++)
		{
            if (vertexBufferData[posIn3Array + l] < bounds[0 + l])
            {
                bounds[0 + l] = vertexBufferData[posIn3Array + l];
            }

            if (vertexBufferData[posIn3Array + l] > bounds[3 + l])
            {
                bounds[3 + l] = vertexBufferData[posIn3Array + l];
            }
		}

        // Read normal components
		vertexData = vertex->FirstChildElement("normal");
        vertexData->QueryFloatAttribute("x", &normalComponentBufferData[posIn3Array]);
        vertexData->QueryFloatAttribute("y", &normalComponentBufferData[posIn3Array+1]);
        vertexData->QueryFloatAttribute("z", &normalComponentBufferData[posIn3Array+2]);

        // Read texture coordinates
		vertexData = vertex->FirstChildElement("texcoord");
        vertexData->QueryFloatAttribute("u", &texCoordBufferData[posIn2Array]);
        vertexData->QueryFloatAttribute("v", &texCoordBufferData[posIn2Array+1]);

        LOGI("vertexData: %3.3f, %3.3f, %3.3f,", vertexBufferData[posIn3Array], vertexBufferData[posIn3Array+1], vertexBufferData[posIn3Array+2]);
        LOGI("normalData: %3.3f, %3.3f, %3.3f,", normalComponentBufferData[posIn3Array], normalComponentBufferData[posIn3Array+1], normalComponentBufferData[posIn3Array+2]);
        LOGI("texcrdData: %3.3f, %3.3f",         texCoordBufferData[posIn2Array], texCoordBufferData[posIn2Array+1]);

		posIn3Array += 3;
		posIn2Array += 2;
		vertex = vertex->NextSiblingElement("vertex");
	}






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
        LOGI("%s %d: new %s", __FILE__, __LINE__, "modelMesh");



		const char* shader = submesh->Attribute("shader");
		if (shader != NULL)
		{
			int length = strnlen(shader, MJMODEL_MAXATTRSIZE)+1;
			modelMesh->shaderName = new char[length];
            LOGI("%s %d: new %s", __FILE__, __LINE__, "char[] for shaderName");

			strncpy(modelMesh->shaderName, shader, length);

		} else
		{
			modelMesh->shaderName = NULL;

		}

		const char* tempStrAttr = submesh->Attribute("material");
		{
			int length = strnlen(tempStrAttr, MJMODEL_MAXATTRSIZE)+1;
			modelMesh->material = new char[length];
            LOGI("%s %d: new %s", __FILE__, __LINE__, "char[] for material");

			strncpy(modelMesh->material, tempStrAttr, length);
		}

		XMLElement* faces = submesh->FirstChildElement("faces");


		faces->QueryIntAttribute("count", &faceCount);

		modelMesh->drawOrderCount = faceCount*3;

		modelMesh->drawOrderBuffer = new unsigned short[faceCount*3];
        LOGI("%s %d: new %s", __FILE__, __LINE__, "short for drawOrder");


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

        checkGlError("load");
        // if using core profile
        checkGlError("load: VAO");


        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelMesh->elementBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, modelMesh->drawOrderCount*sizeof(unsigned short), modelMesh->drawOrderBuffer, GL_STATIC_DRAW);


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
            LOGI("%s %d: new %s", __FILE__, __LINE__, "char[] for submesh");


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
    LOGI("%s %d: new %s", __FILE__, __LINE__, "modelPose");

    for (unsigned i = 0; i < meshes.size(); i++)
    {
        pose->angles.push_back(new mjVector3());
        LOGI("%s %d: new %s", __FILE__, __LINE__, "vector3 for angles");
        pose->positions.push_back(new mjVector3());
        LOGI("%s %d: new %s", __FILE__, __LINE__, "vector3 for positions");
    }
    return pose;
}


}// namespace mj
