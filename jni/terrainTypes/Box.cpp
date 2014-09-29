#include "Box.h"

Box::Box()
: mjObject(MJ_AABB)
{
    model = new mjModel();
    model->LoadFromFile("/sdcard/mjEngineCPP/box.mesh.xml");
    mjAABB* boundingStruct = ((mjAABB*)boundingStructure);
    boundingStruct->isImmovable = true;
    
    mjImageLoader imgLoader;
    GLuint glTexture = imgLoader.LoadToGLAndFreeMemory("/sdcard/mjEngineCPP/box_grassy.png");
    
    for (int i = 0; i<model->meshes.size(); i++)
    {
        model->meshes[i]->glTexture = glTexture;
    }
    
}

