#ifndef PLATFORMUNIVERSESCENE_H
#define PLATFORMUNIVERSESCENE_H


#ifdef ANDROID
#include <jni.h>
#endif


#include "../extLibs/util/mjMultiPlatform.h"

#include "../extLibs/logger/mjLog.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <vector>



#include <core/mjObject.h>
#include <core/mjUniverse.h>
#include <graphics/mjModel.h>

#include <graphics/mjImageLoader.h>
#include <graphics/mjDefaultShaders.h>
#include <graphics/mjSkyboxShaders.h>
#include <core/mjVector3.h>

#include <util/mjResourceManager.h>

#include <extLibs/math/Matrix.h>
#include <graphics/mj3rdPersonCamera.h>
#include <graphics/mjSkybox.h>
#include <physics/mjPhysics.h>
#include <graphics/mjSceneGraph.h>

#include <audio/mjMusicPlayer.h>

#include "entities/Character.h"
#include "entities/GlowBeing.h"
#include "Ambient.h"
#include "Level.h"
#include "EntityCreator.h"

using namespace mjEngine;



class PlatformUniverseScene : public mjUniverse
{
    public:
        const char* sceneName = "platformuniverse";
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

        mjSceneGraph sceneGraph;

        Character* character;

        EntityCreator* entityCreator;

        Ambient ambient;

        PlatformUniverseScene(mjResourceManager* resourceManager);
        void Initialise(int width, int height);

        void InitShaders();
        void SetUpSkybox();
        void Update(double t_elapsed) override;
        void Draw(bool clearFrameBuffer = true) override;

        mjMusicPlayer musicPlayer;
        std::string levelFilename;


        // From tutorial
        void DEBUGInit();
        void DEBUGDraw();
        GLuint programID;
        GLuint MatrixID;
        GLuint ViewMatrixID;
        GLuint ModelMatrixID;
        GLuint Texture;
        GLuint TextureID;


        GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint normalbuffer;
        GLuint elementbuffer;

        GLuint LightID;


    GLuint uDiffuseLightDirectionHandle;
    GLuint uDiffuseLightColorHandle;
    GLuint uAmbientLightColorHandle;


    mjModel* DEBUGvasilisa;
    mjRenderer* debugRenderer;
    mjObject* debugVasiObject;


        //mjAssimpModel* assimpModel;


    protected:
    private:
};

#endif // PlatformUNIVERSESCENE_H
