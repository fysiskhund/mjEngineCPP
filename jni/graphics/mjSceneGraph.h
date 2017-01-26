#ifndef MJSCENEGRAPH_H
#define MJSCENEGRAPH_H

#include <vector>
#include <algorithm>    // std::sort
#include <core/mjObject.h>
#include <graphics/mjShader.h>
#include <graphics/mjCamera.h>
#include <extLibs/math/mjMatrixStack.h>
#include <extLibs/math/Matrix.h>
#include <graphics/renderer/mjRenderer.h>
#include <util/mjResourceManager.h>
#include <text/mjGraphicCharObject.h>
#include <text/mjGraphicText.h>

#if defined(USE_GL3) || defined(USE_GLES2)
#include <graphics/renderer/mjRendererGL.h>

#endif

namespace mjEngine
{

class mjSceneGraph
{
public:

#if defined(USE_GL3) || defined(USE_GLES2)
    mjRendererGL renderer;
#else
    mjRenderer renderer;
#endif


    bool sortTranslucentObjects = true;


    mjMatrixStack matrixStack;

    void Initialize(mjResourceManager* resourceManager);
    void Add(mjObject* object, bool isDrawable=true, bool castsShadow=false, bool isTranslucent=false);
	void Update(float t_elapsed);
    //void AddGroup(std::vector<mjObject*>* group, bool toDrawable=true, bool toShadowCasters=false, bool toTranslucent=false);
    //void RemoveGroup(std::vector<mjObject *>* group);

    // Removes an object relying on its sceneGraph-*-indices NOTE: doesn't work. Left there in case I can think of something to make it work
    // bool Remove(mjObject* objToRemove, bool fromDrawables=true, bool fromShadowCasters=false, bool fromTranslucents=false);

    //! Finds the object and removes it
    bool Remove(mjObject* objToRemove, bool fromDrawables=true, bool fromShadowCasters=false, bool fromTranslucents=false);

    //! Finds the object and removes it, starting from the back
    bool RemoveFromBack(mjObject* objToRemove, bool fromDrawables=true, bool fromShadowCasters=false, bool fromTranslucents=false);

    // Get value to detect whether the index is in use by sceneGraph  NOTE: doesn't work. Left there in case I can think of something to make it work
    //unsigned GetUnusedIndexValue();


	void Draw(mjCamera* camera, std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix);
    void CleanUp();
    ~mjSceneGraph();



private:

    std::vector<mjObject*> drawableObjects;
    std::vector<mjObject*> translucentObjects;
    std::vector<mjObject*> shadowCasters;

    mjResourceManager* resourceManager;
    static bool SortByInvDistanceToCamera(mjObject* obj0,mjObject* obj1);
    void DrawObject(mjObject* drawableObj);

    bool RemoveFromVector(std::vector<mjObject*>* vectorObj, mjObject* object);
    bool RemoveFromVectorFromBack(std::vector<mjObject*>* vectorObj, mjObject* object);

    bool RemoveFromVectorWithIndex(std::vector<mjObject*>* vectorObj, mjObject* object, unsigned index);

    float* lookAtMatrix;
    float* projectionMatrix;




};

}
#endif
