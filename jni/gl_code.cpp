/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

// OpenGL ES 2.0 code

#ifdef ANDROID
#include <jni.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#include "extLibs/logger/mjLog.h"




#include <stdio.h>
#include <stdlib.h>
#include <math.h>






#include "graphics/mjModel.h"
#include "core/mjObject.h"
#include "graphics/mjImageLoader.h"
#include "graphics/mjDefaultShaders.h"
#include "mjVector3.h"
#include "etc/testImage.h"
#include "extLibs/math/Matrix.h"
#include "graphics/mjCamera.h"
#include "physics/mjPhysics.h"

using namespace mjEngine;



mjObject bird(MJ_AABB);
mjObject character(MJ_AABB);
mjObject box0(MJ_AABB);

mjCamera camera;

mjDefaultShaders* defaultShaders = new mjDefaultShaders();

float projectionMatrix[16];

float modelViewProjectionMatrix[16];
float modelViewMatrix[16];
float ratio;
bool debugMatrix = true;
float theta = 0;

mjPhysics physics;


static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}



std::vector<mjShader*> shaderList;

void InitShaders()
{
	mjDefaultShaders* defaultShaders = new mjDefaultShaders();
	shaderList.push_back(defaultShaders);
}
bool setupGraphics(int w, int h) {



    LOGI("setupGraphics(%d, %d)", w, h);

    glEnable(GL_DEPTH_TEST);



    glViewport(0, 0, w, h);
    checkGlError("glViewport");

    LOGI("Before first model");
    box0.model = new mjModel();
    box0.model->LoadFromFile("/sdcard/mjEngineCPP/box.mesh.xml");
    box0.scale.Set(8,8,8);


    box0.dir.Normalize();
    mjAABB* box0BoundingStruct = ((mjAABB*)box0.boundingStructure);
    box0BoundingStruct->isImmovable = true;
    mjVector3 box0HalfScale;
    box0HalfScale.CopyFrom(box0.scale);
    box0HalfScale.MulScalar(0.5);
    box0BoundingStruct->halfWidths.CopyFrom(box0HalfScale);
    box0.pos.Set(0,-4,0);
    box0.Update(0);



    mjImageLoader* imgLoader = new mjImageLoader();//


    imgLoader = new mjImageLoader();
    imgLoader->Load("/sdcard/mjEngineCPP/box_grassy.png");
    GLuint glTexture = imgLoader->SendToGL();
    for (int i = 0; i<box0.model->meshes.size(); i++)
    {
    	box0.model->meshes[i]->glTexture = glTexture;
    }


    bird.model = new mjModel();
    bird.model->LoadFromFile("/sdcard/mjEngineCPP/bird.mesh.xml");
    bird.pos.Set(-2,0,3);
    bird.dir.Set(-1, 0, 1);
    bird.dir.Normalize();
    ((mjAABB*)bird.boundingStructure)->isImmovable = true;
    //((mjSphere*) bird.boundingStructure)->r = 0.3;

    // Test loading png texture

    imgLoader->Load("/sdcard/mjEngineCPP/birdtexture.png");
    glTexture = imgLoader->SendToGL();
    for (int i = 0; i<bird.model->meshes.size(); i++)
    {
    	bird.model->meshes[i]->glTexture = glTexture;
    }
    delete [] imgLoader->imageData;


    character.model = new mjModel();
    character.model->LoadFromFile("/sdcard/mjEngineCPP/char0.mesh.xml");

    character.dir.Set(0, 0, 1);
    character.dir.Normalize();
    mjAABB* charBoundStruct = (mjAABB*) character.boundingStructure;
    mjVector3 minCorner;
    minCorner.Set(-0.3,0,-0.3);
    mjVector3 maxCorner;
    maxCorner.Set(0.3,1.65, 0.3);
    charBoundStruct->SetCorners(minCorner,maxCorner);
    character.pos.Set(0,10,0);
    character.modelOffset.Set(0,-0.825,0);
    //charBoundStruct->SetCorners()
    //((mjSphere*) character.boundingStructure)->r = 0.5;

    //LOGI("texture loading. for obj2");
    imgLoader = new mjImageLoader();
    imgLoader->Load("/sdcard/mjEngineCPP/suit_test.png");
    glTexture = imgLoader->SendToGL();
    for (int i = 0; i<character.model->meshes.size(); i++)
    {
       	character.model->meshes[i]->glTexture = glTexture;
    }

    delete [] imgLoader->imageData;

    float closeUpFactor = 0.1;
    ratio = closeUpFactor*((float)w)/((float)h);
    Matrix4::FrustumM(projectionMatrix, 0,
            				   -ratio, ratio, -closeUpFactor, closeUpFactor, 0.5, 50);

    InitShaders();
    bird.model->TieShaders(shaderList);
    character.model->TieShaders(shaderList);



    physics.AddObject(&bird, 0);
    physics.AddObject(&character, 0);
    physics.AddObject(&box0, 0);


    mjVector3 testDir(1, -1, -1);
    testDir.Normalize();

    mjVector3 testGravity(0,0,1);

    testGravity.Normalize();

    mjVector3 outForwardDir;
    mjVector3 outLeftDir;
    mjMathHelper::GetForwardAndLeftDirections(testDir, testGravity, &outForwardDir, &outLeftDir);

    return true;
}





void renderFrame() {

	// Update phase
	physics.Update(0.016);
	//LOGI("Char.vel: %3.3f, %3.3f, %3.3f", character.vel.x, character.vel.y, character.vel.z);
	//character.Update(0.016);


	float lookAtMatrix[16];
    static float grey = 0.3;
    grey += 0.001f;
    if (grey > 0.7f) {
        grey = 0.3f;
    }
    glClearColor(grey*0.5, grey*0.5, grey, 1.0f);
    checkGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");


    camera.dir.Set(0,0,-1);
    camera.dir.Normalize();
    camera.pos.Set(0,1.6,8);
    camera.GetLookAtMatrix(lookAtMatrix);
    //Matrix4::DebugM("lookat", lookAtMatrix);


    // Apply the transformation as defined by the pose to the modelMatrix
    //mjMatrixHelper.GetPositionScaleAndRotationMatrix(pose.positions.get(0), pose.angles.get(0), localMeshMatrix);

    /////// modelStructure operations should come here

    //mjMatrixHelper.GetPositionScaleAndRotationMatrix(pose.positions.get(currentNodeIndex), pose.angles.get(currentNodeIndex), tempMatrix);

    // Matrix multiplication should come here

    // Apply the lookAt (viewMatrix) transformation to obtain modelView transformation
    //Matrix4::MultiplyMM(modelViewMatrix, 0, viewMatrix, 0, modelMatrix, 0);

    theta+= 0.01;
    if (theta >= 2.0*(3.141592))
    {
    	theta -= 2.0*(3.141592);
    }
    {
    	float x, z;
    	x = sin(theta);
    	z = cos(theta);
    	bird.dir.Set(z, 0, -x);
    	//character.dir.Set(x, 0, z);
    	bird.pos.Set(3.0*x,0,3.0*z);
    }
    character.Draw(shaderList, lookAtMatrix, projectionMatrix);
    bird.Draw(shaderList, lookAtMatrix, projectionMatrix);
    box0.Draw(shaderList, lookAtMatrix, projectionMatrix);

    if (character.pos.y < -5)
    {
    	character.pos.Set0();
    	character.pos.y = 10;
    	character.vel.y = 0;
    }
}

void PrintGLCapabilities()
{
	printGLString("Version", GL_VERSION);
	printGLString("Vendor", GL_VENDOR);
	printGLString("Renderer", GL_RENDERER);
	printGLString("Extensions", GL_EXTENSIONS);
}

extern "C" {
    JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_step(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_HandleJoystickInput(JNIEnv * env, jobject obj, jint controllerID, jint joystickID, jfloat x, jfloat y);
    JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_HandleButtonInput(JNIEnv * env, jobject obj, jint controllerID, jint buttonID, jboolean pressedDown);
};

JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_step(JNIEnv * env, jobject obj)
{
    renderFrame();
}

JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_HandleJoystickInput(JNIEnv * env, jobject obj, jint controllerID, jint joystickID,
		jfloat x, jfloat y)
{
	mjVector3 dir;
	dir.Set(x,0,y);

	float norm = dir.GetNorm();
	if (norm > 0.2)
	{
		character.dir.CopyFrom(dir);
		character.dir.Normalize();
		character.vel.CopyFrom(dir);

	} else {
		character.vel.Set0();
	}

	//LOGI("Controller[%d].joystick[%d]: %3.3f, %3.3f", controllerID, joystickID, x, y);
}

JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_HandleButtonInput(JNIEnv * env, jobject obj, jint controllerID, jint buttonID, jboolean pressedDown)
{

}

