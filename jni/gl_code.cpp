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
#include "graphics/mjImageLoader.h"
#include "graphics/mjDefaultShaders.h"
#include "mjVector3.h"
#include "etc/testImage.h"
#include "extLibs/math/Matrix.h"

using namespace mjEngine;


mjModel* model;
mjDefaultShaders* defaultShaders = new mjDefaultShaders();

float modelMatrix[16];
float viewMatrix[16];
float projectionMatrix[16];

float modelViewProjectionMatrix[16];
float modelViewMatrix[16];
float ratio;
bool debugMatrix = true;

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



    glViewport(0, 0, w, h);
    checkGlError("glViewport");


    model = new mjModel();
    model->LoadFromFile("/sdcard/mjEngineCPP/sprite.mesh.xml");

    // Test loading png texture
    mjImageLoader* imgLoader = new mjImageLoader();//("/sdcard/mjEngineCPP/test.png");
    LOGI("About to load texture");
    if (imgLoader->Load("/sdcard/mjEngineCPP/test.png"))
    {
    	LOGI("Image being loaded is %dx%d", imgLoader->width, imgLoader->height);
    } else
    {
    	LOGI("Image loader returned false -_-*");
    }
    checkGlError("loading image");

    GLuint textures[1];
    glGenTextures(1, &textures[0]);
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    // Set parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgLoader->width, imgLoader->height, 0, imgLoader->hasAlpha? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, imgLoader->imageData);//testImage.pixel_data);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, testImage.pixel_data);
    model->meshes[0]->glTexture = textures[0];

    //delete [] imgLoader->imageData;


    Matrix4::SetIdentityM(modelMatrix,0 );
    Matrix4::SetIdentityM(viewMatrix, 0);
    Matrix4::SetIdentityM(modelViewMatrix,0);

    ratio = ((float)w)/((float)h);
    Matrix4::FrustumM(projectionMatrix, 0,
    				   -ratio, ratio, -1, 1, 0.5, 100);

    InitShaders();
    model->TieShaders(shaderList);

    return true;
}




void renderFrame() {
    static float grey;
    grey += 0.01f;
    if (grey > 1.0f) {
        grey = 0.0f;
    }
    glClearColor(grey, grey, grey, 1.0f);
    checkGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");



    // Apply the transformation as defined by the pose to the modelMatrix
    //mjMatrixHelper.GetPositionScaleAndRotationMatrix(pose.positions.get(0), pose.angles.get(0), localMeshMatrix);

    /////// modelStructure operations should come here

    //mjMatrixHelper.GetPositionScaleAndRotationMatrix(pose.positions.get(currentNodeIndex), pose.angles.get(currentNodeIndex), tempMatrix);

    // Matrix multiplication should come here

    // Apply the lookAt (viewMatrix) transformation to obtain modelView transformation
    //Matrix4::MultiplyMM(modelViewMatrix, 0, viewMatrix, 0, modelMatrix, 0);

    // Calculate the modelViewProjection matrix
    Matrix4::MultiplyMM(modelViewProjectionMatrix, 0, projectionMatrix, 0, modelViewMatrix, 0);

    model->Draw(shaderList, modelViewMatrix, projectionMatrix, modelViewProjectionMatrix);

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
