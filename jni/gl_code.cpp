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
bool hue = false;

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

static const char gVertexShader[] = 
    "attribute vec4 vPosition;\n"
	"attribute vec2 aTexCoordinates;\n"
	"uniform mat4 modelViewProjectionMatrix;\n"

	"varying vec2 vTexCoordinates;\n"
    "void main() {\n"
    "  gl_Position = modelViewProjectionMatrix*vPosition;\n"
	"  vTexCoordinates = aTexCoordinates;\n"
    "}\n";

static const char gFragmentShader[] = 
    "precision mediump float;\n"
	"varying vec2 vTexCoordinates;\n"
	"uniform sampler2D uTexture;\n"
    "void main() {\n"
    "  gl_FragColor = texture2D(uTexture, vTexCoordinates);\n"
    "}\n";

GLuint loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                            shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, gVertexShader);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, gFragmentShader);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint gProgram;
GLuint maPositionHandle;
GLuint maNormalHandle;
GLuint maTextureCoordHandle;
GLuint maTextureHandle;
GLuint maMVPMatrixHandle;
GLuint maMVMatrixHandle;


bool setupGraphics(int w, int h) {


    LOGI("setupGraphics(%d, %d)", w, h);
    gProgram = createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
        LOGE("Could not create program.");
        return false;
    }
    maPositionHandle = glGetAttribLocation(gProgram, "vPosition");
    checkGlError("glGetAttribLocation");
    //maNormalHandle = glGetAttribLocation(gProgram, "aNormal");
    maTextureCoordHandle = glGetAttribLocation(gProgram, "aTexCoordinates");
    maMVPMatrixHandle = glGetUniformLocation(gProgram, "modelViewProjectionMatrix");
    checkGlError("glGetAttribLocation_atex");

    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
    		maPositionHandle);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");







    mjVector3* r = new mjVector3(1,2,3);
    	mjVector3* q = new mjVector3(4,7,6);

    model = new mjModel();
    model->LoadFromFile("/sdcard/mjEngineCPP/sprite.mesh.xml");

    delete r;
    delete q;



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
    model->glTexture = textures[0];

    //delete [] imgLoader->imageData;


    Matrix4::SetIdentityM(modelMatrix,0 );
    Matrix4::SetIdentityM(viewMatrix, 0);


    ratio = ((float)h)/((float)w);
    Matrix4::FrustumM(projectionMatrix, 0,
    				   -ratio, ratio, -1, 1, 1, 100);


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

    glUseProgram(gProgram);
    checkGlError("glUseProgram");

    // Enable a handle to the triangle vertices
    glEnableVertexAttribArray(maPositionHandle);
    checkGlError("glEnableVertexAttribArray");
    glVertexAttribPointer(maPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, model->vertexBuffer);
    checkGlError("glVertexAttribPointer");

    // Enable a handle to the normals..
    //glEnableVertexAttribArray(maNormalHandle);
    //checkGlError("glEnableVertexAttribArray_normals");
    //glVertexAttribPointer(maNormalHandle, 3, GL_FLOAT, GL_FALSE, 0, model->normalComponentBuffer);
    //checkGlError("glVertexAttribPointer");
	
    // Connect the texture
    glActiveTexture(GL_TEXTURE0);
    // Bind the texture handle
    glBindTexture(GL_TEXTURE_2D, model->glTexture);
    // Set the sampler texture unit to 0
    glUniform1i(maTextureHandle, 0);

    // Connect ambient light
    //glUniform4fv(handles.maAmbientLightColorHandle, 1, ambientLightColour, 0);


    // Connect light direction and colour
    //glUniform4fv(handles.maDiffuseLightColorHandle, 1, diffuseLightColour, 0);
    //glUniform3fv(handles.maDiffuseLightDirectionHandle, 1, lightDir, 0);


    //Prepare ("connect") the triangle coordinate data
    // Offset in the buffer, for accessing the texcoord data directly

    glVertexAttribPointer(maTextureCoordHandle, 2,
                    GL_FLOAT, GL_FALSE,
                    0, model->texCoordBuffer);

    // Enable a handle to the texture coordinates
    glEnableVertexAttribArray(maTextureCoordHandle);


    // Apply the transformation as defined by the pose to the modelMatrix
    //mjMatrixHelper.GetPositionScaleAndRotationMatrix(pose.positions.get(0), pose.angles.get(0), localMeshMatrix);

    /////// modelStructure operations should come here

    //mjMatrixHelper.GetPositionScaleAndRotationMatrix(pose.positions.get(currentNodeIndex), pose.angles.get(currentNodeIndex), tempMatrix);

    // Matrix multiplication should come here

    // Apply the lookAt (viewMatrix) transformation to obtain modelView transformation
    Matrix4::MultiplyMM(modelViewMatrix, 0, viewMatrix, 0, modelMatrix, 0);

    if (hue == false)
    {
    	for (int i = 0; i < 16; i++)
    	{
    		LOGI("%3.3f, ", projectionMatrix[i]);
    	}

    	LOGI("----");
    }

    // Calculate the modelViewProjection matrix
    Matrix4::MultiplyMM(modelViewProjectionMatrix, 0, projectionMatrix, 0, modelViewMatrix, 0);

    if (hue == false)
    {
    	for (int i = 0; i < 16; i++)
    	{
    		LOGI("%3.3f, ", projectionMatrix[i]);
    	}
    	hue = true;
    }
    /////////


    // Insert the handles for the transformation matrix
    glUniformMatrix4fv(maMVPMatrixHandle, 1, false, modelViewProjectionMatrix);
    //glUniformMatrix4fv(maMVMatrixHandle, 1, false, modelViewMatrix);


	mjModelMesh* mesh = model->meshes[0];
    glDrawElements(GL_TRIANGLES, mesh->drawOrderCount, GL_UNSIGNED_SHORT, mesh->drawOrderBuffer);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
    checkGlError("glDrawArrays");
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
