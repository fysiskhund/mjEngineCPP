/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

// OpenGL ES 2.0 code

#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define  LOG_TAG    "mj"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)




#include "graphics/mjModel.h"
#include "core/mjObject.h"
#include "graphics/mjImageLoader.h"
#include "graphics/mjDefaultShaders.h"
#include "mjVector3.h"
#include "etc/testImage.h"
#include "extLibs/math/Matrix.h"
#include "graphics/mjCamera.h"

using namespace mjEngine;



mjObject testObject;
mjObject testObject2;
mjCamera camera;

mjDefaultShaders* defaultShaders = new mjDefaultShaders();

float projectionMatrix[16];

float modelViewProjectionMatrix[16];
float modelViewMatrix[16];
float ratio;
bool debugMatrix = true;
float theta = 0;


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
    testObject.model = new mjModel();
    testObject.model->LoadFromFile("/sdcard/mjEngineCPP/bird.mesh.xml");
    testObject.pos.Set(-2,0,3);
    testObject.dir.Set(-1, 0, 1);
    testObject.dir.Normalize();

    // Test loading png texture
    mjImageLoader* imgLoader = new mjImageLoader();//
    imgLoader->Load("/sdcard/mjEngineCPP/birdtexture.png");
    GLuint glTexture = imgLoader->SendToGL();
    for (int i = 0; i<testObject.model->meshes.size(); i++)
    {
    	testObject.model->meshes[i]->glTexture = glTexture;
    }
    delete [] imgLoader->imageData;

    LOGI("Before second model");
    testObject2.model = new mjModel();
    testObject2.model->LoadFromFile("/sdcard/mjEngineCPP/char0.mesh.xml");
    testObject2.pos.Set(-3,0,4);
    testObject2.dir.Set(1, 0, 1);
    testObject2.dir.Normalize();

    LOGI("texture loading. for obj2");
    imgLoader = new mjImageLoader();
    imgLoader->Load("/sdcard/mjEngineCPP/suit_test.png");
    glTexture = imgLoader->SendToGL();
    for (int i = 0; i<testObject2.model->meshes.size(); i++)
    {
       	testObject2.model->meshes[i]->glTexture = glTexture;
    }

    delete [] imgLoader->imageData;

    ratio = ((float)w)/((float)h);
    Matrix4::FrustumM(projectionMatrix, 0,
            				   -ratio, ratio, -1.0, 1.0, 1, 20);

    InitShaders();
    testObject.model->TieShaders(shaderList);
    testObject2.model->TieShaders(shaderList);
    return true;
}





void renderFrame() {
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


    camera.dir.Set(1,0,1);
    camera.dir.Normalize();
    camera.pos.Set(0,0,-10);
    camera.GetLookAtMatrix(lookAtMatrix);
    //Matrix4::DebugM("lookat", lookAtMatrix);


    // Apply the transformation as defined by the pose to the modelMatrix
    //mjMatrixHelper.GetPositionScaleAndRotationMatrix(pose.positions.get(0), pose.angles.get(0), localMeshMatrix);

    /////// modelStructure operations should come here

    //mjMatrixHelper.GetPositionScaleAndRotationMatrix(pose.positions.get(currentNodeIndex), pose.angles.get(currentNodeIndex), tempMatrix);

    // Matrix multiplication should come here

    // Apply the lookAt (viewMatrix) transformation to obtain modelView transformation
    //Matrix4::MultiplyMM(modelViewMatrix, 0, viewMatrix, 0, modelMatrix, 0);

    theta+= 0.1;
    if (theta >= 2.0*(3.141592))
    {
    	theta -= 2.0*(3.141592);
    }
    {
    	float x, z;
    	x = sin(theta);
    	z = cos(theta);
    	testObject.dir.Set(x, 0, z);
    	testObject2.dir.Set(x, 0, z);
    	testObject.pos.Set(3.0*x,0,3.0*z);
    }
    testObject.Draw(shaderList, lookAtMatrix, projectionMatrix);
    testObject2.Draw(shaderList, lookAtMatrix, projectionMatrix);

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
};

JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_step(JNIEnv * env, jobject obj)
{
    renderFrame();
}
