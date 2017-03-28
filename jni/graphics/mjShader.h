/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJSHADER_H
#define MJSHADER_H

#include <stdlib.h>


#ifdef USE_ASSIMP
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#endif

#include <graphics/mjModelMesh.h>

#include "../core/mjVector3.h"

#include "../extLibs/util/mjMultiPlatform.h"

#include "../extLibs/logger/mjLog.h"


namespace mjEngine
{
    typedef enum {
        MJ_VERTEX_COORDINATES_GLVERTEXATTRIB_ID = 0,
        MJ_NORMAL_COORDINATES_GLVERTEXATTRIB_ID,
        MJ_COLOR_GLVERTEXATTRIB_ID,
        MJ_UV_COMPONENTS_GLVERTEXATTRIB_ID,
        MJ_UV_COMPONENTS_SECONDARY_TEXTURE_GLVERTEXATTRIB_ID
    
    
    } MJVERTEX_ATTRIB; // Coincide with iOS GLKVertexAttrib constants


class mjShader{
public:
    GLuint glProgramHandle;
    GLuint glVertexShaderHandle;
    GLuint glFragmentShaderHandle;

    char* name;

    /* renderer toggles */
    bool enableDepthTest = true;
    bool enableDepthMask = true;

    virtual void BindAttributeLocations();

    virtual void Run(mjModelMesh* modelMesh,
            float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
            float* modelMatrix, float* modelViewProjectionMatrix, int glTexture, float* extraColorForTexture)= 0; // Gets called in order to draw something

    virtual void BindTexCoordBuffer(float* texCoordBuffer) = 0;
    virtual void BindMatrices(float* modelMatrix, float* modelViewProjectionMatrix) = 0;
    virtual void BindTexture(int glTexture) = 0;
    virtual void BindExtraColorForTexture( float* extraColorForTexture) = 0;

#ifdef USE_ASSIMP

    virtual void RunForAssimp(const aiMesh* assimpMesh, mjModelMesh* mjMesh,
                      float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
                      float* modelMatrix, float* modelViewProjectionMatrix, int glTexture) = 0;

#endif


	GLuint LoadShader(GLenum shaderType, const char* pSource);
	void CreateProgram(const char* vertexShadercode, const char* fragmentShaderCode);
};

}

#endif
