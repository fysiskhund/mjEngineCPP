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
void mjModel::LoadFromFile(char* fileName)
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

	while(submesh)
	{
		mjModelMesh* modelMesh = new mjModelMesh();

		const char* tempStrAttr = submesh->Attribute("material");
		modelMesh->material = new char[strnlen(tempStrAttr, 96)+1];
		strncpy(modelMesh->material, tempStrAttr, 96);

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
		meshes.push_back(modelMesh);
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

		const char* tempStrAttr = submesh->Attribute("name");
		meshes[desiredIndex]->name = new char[strnlen(tempStrAttr, 96)+1];
		strncpy(meshes[desiredIndex]->name, tempStrAttr, 96);
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

void mjModel::Draw()
{
	for(int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Draw();
	}
}

}// namespace mj
