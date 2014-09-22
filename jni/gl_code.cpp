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
#include <unistd.h>






#include "graphics/mjModel.h"
#include "core/mjObject.h"
#include "graphics/mjImageLoader.h"
#include "graphics/mjDefaultShaders.h"
#include "graphics/mjSkyboxShaders.h"
#include "mjVector3.h"
#include "etc/testImage.h"
#include "extLibs/math/Matrix.h"
#include "graphics/mj3rdPersonCamera.h"
#include "graphics/mjSkybox.h"
#include "physics/mjPhysics.h"
#include "Character.h"

using namespace mjEngine;



mjObject bird(MJ_AABB);
Character character(MJ_AABB);
mjObject box0(MJ_AABB);
mjSkybox skybox;

mj3rdPersonCamera camera;

mjDefaultShaders* defaultShaders = new mjDefaultShaders();

float projectionMatrix[16];

float modelViewProjectionMatrix[16];
float modelViewMatrix[16];
float ratio;
bool debugMatrix = true;
float theta = 0;

mjPhysics physics;


mjVector3 cameraAnglesModifier;


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
	mjSkyboxShaders* skyboxShaders = new mjSkyboxShaders();

	shaderList.push_back(defaultShaders);
	shaderList.push_back(skyboxShaders);
}

void SetUpSkybox()
{
	mjImageLoader imgLoader;
	mjModel* skyboxBox = new mjModel();
	skyboxBox->LoadFromFile("/sdcard/mjEngineCPP/skybox.mesh.xml");

	mjModel* skyboxPlane = new mjModel();
	skyboxPlane->LoadFromFile("/sdcard/mjEngineCPP/skybox_plane.mesh.xml");

	skybox.SetModels(skyboxBox, skyboxPlane);

	skybox.LoadTexturesFromPrefix("/sdcard/mjEngineCPP/bluesky/skybox");

	char wanderingCloudName[1024];
	for (int i = 0; i < 3; i++)
	{
		snprintf(wanderingCloudName, 1024, "%s%d%s",  "/sdcard/mjEngineCPP/bluesky/wandering_cloud", i, ".png");
		GLuint tex0 = imgLoader.LoadToGLAndFreeMemory(wanderingCloudName);
		skybox.PushLevel(new mjSkyboxLevelData(tex0, i, 0, 0.01*i+0.02, 0));
	}




	skybox.SetCameraPos(&camera.pos);

	LOGI("after SetCamerapos");
}


bool setupGraphics(int w, int h) {
	sleep(3); // For debugger to be able to attach
	// Some adjustments
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	InitShaders();

    LOGI("setupGraphics(%d, %d)", w, h);

    glEnable(GL_DEPTH_TEST);



    glViewport(0, 0, w, h);
    checkGlError("glViewport");


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

LOGI("Before first imgload");
    imgLoader = new mjImageLoader();

    GLuint glTexture = imgLoader->LoadToGLAndFreeMemory("/sdcard/mjEngineCPP/box_grassy.png");

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

    //LOGI("Here");
    glTexture = imgLoader->LoadToGLAndFreeMemory("/sdcard/mjEngineCPP/birdtexture.png");//("/sdcard/mjEngineCPP/bluesky/wandering_cloud0.png"); //
    for (int i = 0; i<bird.model->meshes.size(); i++)
    {
    	bird.model->meshes[i]->glTexture = glTexture;
    }


    character.model = new mjModel();
    character.model->LoadFromFile("/sdcard/mjEngineCPP/char0.mesh.xml");
    character.gravity = &physics.gravity;

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


    mjVector3 cameraOffset;
    cameraOffset.Set(0,0.7,0);
    camera.SetTarget(&character.pos, cameraOffset);
    camera.r = 10;

    //charBoundStruct->SetCorners()
    //((mjSphere*) character.boundingStructure)->r = 0.5;

    LOGI("or here");
    glTexture = imgLoader->LoadToGLAndFreeMemory("/sdcard/mjEngineCPP/suit_test.png");
    for (int i = 0; i<character.model->meshes.size(); i++)
    {
       	character.model->meshes[i]->glTexture = glTexture;
    }



    float closeUpFactor = 0.1;
    ratio = closeUpFactor*((float)w)/((float)h);
    Matrix4::FrustumM(projectionMatrix, 0,
            				   -ratio, ratio, -closeUpFactor, closeUpFactor, 0.5, 50);





    bird.model->TieShaders(shaderList);
    character.model->TieShaders(shaderList);
    box0.model->TieShaders(shaderList);

    SetUpSkybox();
    skybox.TieShaders(shaderList);



    physics.AddObject(&bird, 0);
    physics.AddObject(&character, 0);
    physics.AddObject(&box0, 0);

    LOGI("End of init");
    return true;
}





void renderFrame(float t_elapsed) {

	// Update phase
	physics.Update(t_elapsed);
	camera.Update(t_elapsed);
	skybox.Update(t_elapsed);
	if (cameraAnglesModifier.GetNorm() > 0.2) {
		camera.theta += -0.02*cameraAnglesModifier.y;
		if (camera.theta > 6.283184)
			camera.theta -= 6.283184;
		else if (camera.theta < 0)
			camera.theta = 6.283184 + camera.theta;

		camera.phi += -0.02*cameraAnglesModifier.x;

		if (camera.phi > 6.283184)
			camera.phi -= 6.283184;
		else if (camera.phi < 0)
			camera.phi = 6.283184 + camera.phi;

	} else
	{
		cameraAnglesModifier.Set0();
	}
	//LOGI("camera.dir: %3.3f, %3.3f, %3.3f", camera.dir.x, camera.dir.y, camera.dir.z);
	//character.Update(0.016);


	///////// Draw start

	float lookAtMatrix[16];

    glClearColor(1, 0, 0, 1.0f);
    //checkGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    //checkGlError("glClear");



    //camera.dir.Set(0,0,-1);
    //camera.dir.Normalize();
    //camera.pos.Set(0,1.6,8);

    camera.GetLookAtMatrix(lookAtMatrix);
    skybox.Draw(shaderList, lookAtMatrix, projectionMatrix);


    //Matrix4::DebugM("lookat", lookAtMatrix);


    // Apply the transformation as defined by the pose to the modelMatrix
    //mjMatrixHelper.GetPositionScaleAndRotationMatrix(pose.positions.get(0), pose.angles.get(0), localMeshMatrix);

    /////// modelStructure operations should come here

    //mjMatrixHelper.GetPositionScaleAndRotationMatrix(pose.positions.get(currentNodeIndex), pose.angles.get(currentNodeIndex), tempMatrix);

    // Matrix multiplication should come here

    // Apply the lookAt (viewMatrix) transformation to obtain modelView transformation
    //Matrix4::MultiplyMM(modelViewMatrix, 0, viewMatrix, 0, modelMatrix, 0);

    //LOGI("%s:%d hasn't crashed yet", __FILE__, __LINE__);
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
    //LOGI("%s:%d hasn't crashed yet", __FILE__, __LINE__);
    character.Draw(shaderList, lookAtMatrix, projectionMatrix);
    //LOGI("%s:%d hasn't crashed yet", __FILE__, __LINE__);
    bird.Draw(shaderList, lookAtMatrix, projectionMatrix);
    //LOGI("%s:%d hasn't crashed yet", __FILE__, __LINE__);
    box0.Draw(shaderList, lookAtMatrix, projectionMatrix);
    //LOGI("%s:%d hasn't crashed yet", __FILE__, __LINE__);

    if (character.pos.y < -5)
    {
    	character.pos.Set0();
    	character.pos.y = 10;
    	character.vel.y = 0;
    }
    //LOGI("After renderFrame");
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
    JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_step(JNIEnv * env, jobject obj, jfloat t_elapsed);
    JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_HandleJoystickInput(JNIEnv * env, jobject obj, jint controllerID, jint joystickID, jfloat x, jfloat y);
    JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_HandleButtonInput(JNIEnv * env, jobject obj, jint controllerID, jint buttonID, jboolean pressedDown);
};

JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_step(JNIEnv * env, jobject obj, jfloat t_elapsed)
{
    renderFrame(t_elapsed);
}




JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_HandleJoystickInput(JNIEnv * env, jobject obj, jint controllerID, jint joystickID,
		jfloat x, jfloat y)
{

	if (joystickID == 0)
	{
		mjVector3 dir;
		dir.Set(x,0,y);

		float norm = dir.GetNorm();
		if (norm > 0.2)
		{
			mjVector3 outForwardDir;
			mjVector3 outLeftDir;

			//invGravity.Normalize();
			mjMathHelper::GetForwardAndLeftDirections(camera.dir, physics.gravity, &outForwardDir, &outLeftDir);

			mjVector3 finalForwardDir;
			// The joystick directions need to be inverted because technically they are:
			// in the Y axis, the joystick going "up" outputs a negative y value and viceversa.
			// In the X axis, pushing the joystick towards the left results in a negative value.
			// conceptually it needs to be inverted.
			//

			finalForwardDir.ScaleAdd(-y, outForwardDir);
			finalForwardDir.ScaleAdd(-x, outLeftDir);


			character.vel.CopyFrom(finalForwardDir);
			character.vel.MulScalar(2);
			character.dir.CopyFrom(finalForwardDir);
			character.dir.Normalize();
			/*LOGI("initialDir %3.3f, %3.3f, %3.3f", dir.x, dir.y, dir.z);
			LOGI("cameraDir %3.3f, %3.3f, %3.3f", camera.dir.x, camera.dir.y, camera.dir.z);
			LOGI("finalforwarddir %3.3f, %3.3f, %3.3f", finalForwardDir.x, finalForwardDir.y, finalForwardDir.z);*/

		} else {
			character.vel.Set0();
		}
	} else
	{

		cameraAnglesModifier.Set(x,y,0);




	}


	//LOGI("Controller[%d].joystick[%d]: %3.3f, %3.3f", controllerID, joystickID, x, y);
}

JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_HandleButtonInput(JNIEnv * env, jobject obj, jint controllerID, jint buttonID, jboolean pressedDown)
{
	if (character.footing== 1)
	{
		LOGI("Char: footing -> no");
		character.footing = 0;
		character.vel.ScaleAdd(-1, physics.gravity);
	}
}

