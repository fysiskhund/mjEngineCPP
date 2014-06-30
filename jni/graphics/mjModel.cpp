#include "mjModel.h"

mjModel::mjModel()
{
	numVertices = -1;
	currentVertex = -1;
	currentFace = -1;
}

void mjModel::Load(char* modelDefinition)
{
	//hie
	XMLDocument doc;

	doc.Parse( modelDefinition );

	XMLElement* mesh = doc.FirstChildElement("mesh");
	XMLElement* sharedGeometry = mesh->FirstChildElement("sharedgeometry");
	sharedGeometry->QueryIntAttribute("vertexcount", &numVertices);


	int posIn3Array = 0;
	int posIn2Array = 0;
	vertexBuffer = new float[3*numVertices];
	normalComponentBuffer = new float[3*numVertices];
	texCoordBuffer = new float[2*numVertices];

	XMLElement* vertex = sharedGeometry->FirstChildElement("vertexbuffer")->FirstChildElement("vertex");

	while(vertex)
	{

		XMLElement* vertexData;
		vertexData = vertex->FirstChildElement("position");
		vertexData->QueryFloatAttribute("x", &texCoordBuffer[posIn3Array]);
		vertexData->QueryFloatAttribute("y", &texCoordBuffer[posIn3Array+1]);
		vertexData->QueryFloatAttribute("z", &texCoordBuffer[posIn3Array+2]);

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

}
