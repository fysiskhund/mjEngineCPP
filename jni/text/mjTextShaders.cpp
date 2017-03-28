#include "mjTextShaders.h"

namespace mjEngine {

#ifdef USE_GLES2

    #include "gles2/textShaderSources-gles2.h"

#else

    #include "gl3/textShaderSources-gl3.h"

#endif

mjTextShaders::mjTextShaders()
{
    // Set up shader
    CreateProgram(vertexShaderCode, fragmentShaderCode);

    name = new char[5];
    LOGI("%s %d: new %s", __FILE__, __LINE__, "char[] for shaderName");



    // Get the texture handle location
    maTextureHandle = glGetUniformLocation(glProgramHandle, "uTexture");

    maMVPMatrixHandle = glGetUniformLocation(glProgramHandle, "maMVPMatrix");

    uExtraColorForTextureHandle = glGetUniformLocation(glProgramHandle, "uExtraColorForTexture");


    strncpy(name, "text", 5);

    checkGlError("getting parameters");
}




void mjTextShaders::Run(mjModelMesh *modelMesh, float *vertexBuffer, float *texCoordBuffer, float *normalComponentBuffer, float *modelMatrix, float *modelViewProjectionMatrix, int glTexture, float *extraColorForTexture)
{
    glUseProgram(glProgramHandle);

    // Send the modelViewProjection Matrix
    glUniformMatrix4fv(maMVPMatrixHandle, 1, false, modelViewProjectionMatrix);

    // The modelview matrix is not necessary because the normals are not taken into account.
    // (but maybe this will change to render text that is supposed to be part of the gameworld and not just the UI?)

    // Connect the texture
    glActiveTexture(GL_TEXTURE0);
    // Bind the texture handle
    glBindTexture(GL_TEXTURE_2D, glTexture);
    // Set the sampler texture unit to 0
    glUniform1i(maTextureHandle, 0);
    // Set the extra colour
    glUniform4fv(uExtraColorForTextureHandle, 1, extraColorForTexture);

}

}


void mjEngine::mjTextShaders::BindTexCoordBuffer(float* texCoordBuffer)
{
}

void mjEngine::mjTextShaders::BindMatrices(float* modelMatrix, float* modelViewProjectionMatrix)
{
    // Send the modelViewProjection Matrix
    glUniformMatrix4fv(maMVPMatrixHandle, 1, false, modelViewProjectionMatrix);

    // The modelview matrix is not necessary because the normals are not taken into account.
    // (but maybe this will change to render text that is supposed to be part of the gameworld and not just the UI?)
}

void mjEngine::mjTextShaders::BindTexture(int glTexture)
{
    // Connect the texture
    //glActiveTexture(GL_TEXTURE0); // So far I haven't used more than one texture so..
    // Bind the texture handle
    glBindTexture(GL_TEXTURE_2D, glTexture);
    // Set the sampler texture unit to 0
    glUniform1i(maTextureHandle, 0);
}

void mjEngine::mjTextShaders::BindExtraColorForTexture(float* extraColorForTexture)
{
    // Set the extra colour
    glUniform4fv(uExtraColorForTextureHandle, 1, extraColorForTexture);
}
