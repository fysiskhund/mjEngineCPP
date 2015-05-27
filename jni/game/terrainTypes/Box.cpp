#include "Box.h"

Box::Box(mjResourceManager* resourceManager)
: mjObject(MJ_AABB, resourceManager)
{
    useModelFromXMLDetails = true;

    GLuint glTexture;


    model = resourceManager->FetchModel("bush.mesh.xml");
    glTexture = resourceManager->FetchTexture("bush.png", GL_CLAMP_TO_EDGE);


    mjAABB* boundingStruct = ((mjAABB*)boundingStructure);


    boundingStruct->isImmovable = true;



    for (unsigned i = 0; i<model->meshes.size(); i++)
    {
        model->meshes[i]->glTexture = glTexture;
    }

}

