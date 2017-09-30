#include "Box.h"

Box::Box(mjResourceManager* resourceManager)
: mjObject( resourceManager, MJ_AABB)
{
    useModelFromXMLDetails = true;

    GLuint glTexture;

    glTexture = resourceManager->FetchTexture("entities/box/box_grassy.png", GL_CLAMP_TO_EDGE);
    model = resourceManager->FetchModel("entities/box/box.mesh.xml");



    mjAABB* boundingStruct = ((mjAABB*)boundingStructure);


    boundingStruct->isImmovable = true;



    for (unsigned i = 0; i<model->meshes.size(); i++)
    {
        model->meshes[i]->glTexture = glTexture;
    }

}

