#ifndef PLATFORMUNIVERSESCENE_H
#define PLATFORMUNIVERSESCENE_H


#ifdef ANDROID
#include <jni.h>
#endif


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "../extLibs/logger/mjLog.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "../core/mjObject.h"
#include "../core/mjScene.h"
#include "../graphics/mjModel.h"

#include "../graphics/mjImageLoader.h"
#include "../graphics/mjDefaultShaders.h"
#include "../graphics/mjSkyboxShaders.h"
#include "../core/mjVector3.h"

#include "../extLibs/math/Matrix.h"
#include "../graphics/mj3rdPersonCamera.h"
#include "../graphics/mjSkybox.h"
#include "../physics/mjPhysics.h"
#include "../graphics/mjSceneGraph.h"
#include "../entities/Character.h"
#include "Level.h"
#include "EntityCreator.h"

using namespace mjEngine;


class PlatformUniverseScene : public mjScene
{
    public:
        mjSkybox* skybox;

        mj3rdPersonCamera* camera;

        mjDefaultShaders* defaultShaders;

        float projectionMatrix[16];

        float modelViewProjectionMatrix[16];
        float modelViewMatrix[16];
        float ratio;
        bool debugMatrix = true;
        float theta = 0;

        Level* level;

        mjVector3 cameraAnglesModifier;

        mjSceneGraph* sceneGraph;

        Character* character;

        EntityCreator entityCreator;


        PlatformUniverseScene();
        void InitShaders();
        void SetUpSkybox();
        void Update(float t_elapsed) override;
        void Draw() override;
    protected:
    private:
};

#endif // PlatformUNIVERSESCENE_H
