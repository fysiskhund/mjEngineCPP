#ifndef MJTEXTSHADERS_H
#define MJTEXTSHADERS_H

#include "../graphics/mjShader.h"

namespace mjEngine {

class mjTextShaders : public mjShader
{
public:
    mjTextShaders();

    // mjShader interface
public:

    static const char* vertexShaderCode; // Vanilla shaders give a flat shading of surfaces
    static const char* fragmentShaderCode;

    // Handles
    GLint maPositionHandle;
    GLint maTextureCoordHandle;
    GLint maTextureHandle;
    GLint maMVPMatrixHandle;
    GLint uExtraColorForTextureHandle;


    void Run(mjModelMesh *modelMesh, float *vertexBuffer, float *texCoordBuffer, float *normalComponentBuffer, float *modelMatrix, float *modelViewProjectionMatrix, int glTexture, float *extraColorForTexture) override;

    // mjShader interface
public:
    void BindTexCoordBuffer(float* texCoordBuffer) override;
    void BindMatrices(float* modelMatrix, float* modelViewProjectionMatrix) override;
    void BindTexture(int glTexture) override;
    void BindExtraColorForTexture(float* extraColorForTexture) override;
};

}
#endif // MJTEXTSHADERS_H
