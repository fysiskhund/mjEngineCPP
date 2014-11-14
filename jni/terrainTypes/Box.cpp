#include "Box.h"

Box::Box(mjResourceManager& resourceManager)
: mjObject(MJ_AABB)
{

    model = resourceManager.FetchModel("box.mesh.xml");

    mjAABB* boundingStruct = ((mjAABB*)boundingStructure);
    boundingStruct->isImmovable = true;


    GLuint glTexture = resourceManager.FetchTexture("box_grassy.png");

    for (unsigned i = 0; i<model->meshes.size(); i++)
    {
        model->meshes[i]->glTexture = glTexture;
    }

}

