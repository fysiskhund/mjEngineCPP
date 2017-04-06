#ifndef MJMATERIALBUCKET_H
#define MJMATERIALBUCKET_H

#include <vector>
#include "../core/mjObject.h"
#include "mjShader.h"

namespace mjEngine {

class mjMaterialBucket
{
public:

    bool isNullMaterialBucket = false;
    mjShader* shader;
    unsigned int texture;
    mjResourceManager* resourceManager;
    //float extraColorForTexture[4] = {1, 1, 1, 1};


    std::vector<mjObject*> objects;

    mjMaterialBucket(mjObject* exampleObject, mjResourceManager* resourceManager, bool addObject = true);
    ~mjMaterialBucket();
    mjMaterialBucket* AddObjectIfItBelongs(mjObject* object);
    mjMaterialBucket* ForceAddObject(mjObject* object);
    bool RemoveObject(mjObject* object, bool forceRemove = false);
    bool TestIfObjectBelongs(mjObject* exampleObject);
};

}


#endif // MJMATERIALBUCKET_H
