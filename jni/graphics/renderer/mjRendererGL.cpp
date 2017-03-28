#include "mjRendererGL.h"

namespace  mjEngine {


void mjRendererGL::PrepareModel(mjModel &model)
{

    mjRendererDataGL* dataGL = new mjRendererDataGL();
    LOGI("%s %d: new %s", __FILE__, __LINE__, "dataGL");

    model.rendererData = dataGL;

        checkGlError("starting with PrepareForModel");

#ifndef USE_GLES2
        glGenVertexArrays(1, &dataGL->vertexArrayID);
        LOGI("%s %d: new %s", __FILE__, __LINE__, "glGenVertexArrays");
        checkGlError("creating VAO");
        glBindVertexArray(dataGL->vertexArrayID);
        checkGlError("binding newly created VAO");
#endif




        glGenBuffers(1, &dataGL->vertexCoordinatesBufferID);
        LOGI("%s %d: new %s", __FILE__, __LINE__, "glGenBuffers (vertex)");
        glBindBuffer(GL_ARRAY_BUFFER, dataGL->vertexCoordinatesBufferID);
        glBufferData(GL_ARRAY_BUFFER, model.numVertices * sizeof(GLfloat)*3, model.vertexBufferData, GL_STATIC_DRAW);

        glGenBuffers(1, &dataGL->uvComponentsBufferID);
        LOGI("%s %d: new %s", __FILE__, __LINE__, "glGenBuffers (uv components)");
        glBindBuffer(GL_ARRAY_BUFFER, dataGL->uvComponentsBufferID);
        glBufferData(GL_ARRAY_BUFFER, model.numVertices * sizeof(GLfloat)*2, model.texCoordBufferData, GL_STATIC_DRAW);

        glGenBuffers(1, &dataGL->normalCoordinatesID);
        LOGI("%s %d: new %s", __FILE__, __LINE__, "glGenBuffers (normal coords)");
        glBindBuffer(GL_ARRAY_BUFFER, dataGL->normalCoordinatesID);
        glBufferData(GL_ARRAY_BUFFER, model.numVertices * sizeof(GLfloat)*3, model.normalComponentBufferData, GL_STATIC_DRAW);

        LOGI("Created buffers- VAO %d;  vertexC %d;  uvC %d;  norC %d\n", dataGL->vertexArrayID, dataGL->vertexCoordinatesBufferID,
             dataGL->uvComponentsBufferID, dataGL->normalCoordinatesID);

        checkGlError("defining buffers");

        // Generate a buffer for the indices as well
        dataGL->elementBuffersIDs = new GLuint[model.meshes.size()];
        LOGI("%s %d: new %s", __FILE__, __LINE__, "GLuint[] for meshNums");
        glGenBuffers(model.meshes.size(), dataGL->elementBuffersIDs);
        LOGI("%s %d: new %s", __FILE__, __LINE__, "glGenBuffers (elements)");

        for (uint16_t i = 0; i < model.meshes.size(); i++)
        {
            mjModelMesh* mesh = model.meshes[i];
            /*if (mesh->mjShaderListIndex == -1)
            {
                mesh->mjShaderListIndex = resourceManager->FetchShader(mesh->shaderName)->shaderListIndex;
            }*/ // This will now be done by the resourceManager after model load

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dataGL->elementBuffersIDs[i]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->drawOrderCount * sizeof(unsigned short), mesh->drawOrderBuffer , GL_STATIC_DRAW);
        }
        checkGlError("defining element buffers");
}

void mjRendererGL::RenderModel(mjModel &model, float *modelMatrix, float *lookAtMatrix, float *projectionMatrix, mjModelPose *pose, mjMatrixStack *stack,
                               std::vector<mjShader*>* customShaders, int* customTextures, float* extraColorForTexture, std::vector<mjShader*>& shaderList)
{
    mjRendererDataGL* dataGL = (mjRendererDataGL*) model.rendererData;

    if (&model != naiveLastModel) // Naïve optimisation attempt
    {
        naiveLastModel = &model;


#ifndef USE_GLES2
    glBindVertexArray(dataGL->vertexArrayID);
#endif

        glEnableVertexAttribArray(MJ_VERTEX_COORDINATES_GLVERTEXATTRIB_ID); // Tell OpenGL we will use the slot 0, which we arbitrarily defined as vertex coordinate buffer when the shader source codes were loaded
        glBindBuffer(GL_ARRAY_BUFFER, dataGL->vertexCoordinatesBufferID);
        glVertexAttribPointer(MJ_VERTEX_COORDINATES_GLVERTEXATTRIB_ID, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // vertexBuffer); // According to da internetz, when using VAOs, the last parameter becomes an offset and not a memory address

        glEnableVertexAttribArray(MJ_NORMAL_COORDINATES_GLVERTEXATTRIB_ID); // Tell OpenGL we will use the slot 2, which we arbitrarily defined as the coordinates of the normals when the shader source codes were loaded
        glBindBuffer(GL_ARRAY_BUFFER, dataGL->normalCoordinatesID);
        glVertexAttribPointer(MJ_NORMAL_COORDINATES_GLVERTEXATTRIB_ID, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // normalComponentBuffer); // According to da internetz, when using VAOs, the last parameter becomes an offset and not a memory address

        glEnableVertexAttribArray(MJ_UV_COMPONENTS_GLVERTEXATTRIB_ID); // Tell OpenGL we will use the slot 1, which we arbitrarily defined as UV components when the shader source codes were loaded
        glBindBuffer(GL_ARRAY_BUFFER, dataGL->uvComponentsBufferID);
        glVertexAttribPointer(MJ_UV_COMPONENTS_GLVERTEXATTRIB_ID, 2, GL_FLOAT, GL_FALSE, 0, nullptr); // texCoordBuffer); // According to da internetz, when using VAOs, the last parameter becomes an offset and not a memory address
    }

    checkGlError("After binding Vertex Array Pointers");

    for (uint16_t i = 0; i < model.meshes.size(); i++)
    {
        mjModelMesh* mesh = model.meshes[i];
        mjShader* shader;
        GLuint glTexture;


        shader = customShaders?
                    (customShaders->size() > 1)? (*customShaders)[i] : (*customShaders)[0] :
                    shaderList[mesh->mjShaderListIndex];

        // Is equivalent to this:
        /*
        if (customShaders != NULL)
        {
            if (customShaders->size() > 1)
            {
                shader = (*customShaders)[i];
            } else
            {
                shader = (*customShaders)[0];
            }
        } else
        {
            shader = resourceManager->shaderList[mesh->mjShaderListIndex];

        } */
        // but maybe it's faster than the ifs, who knows..


        glTexture = customTextures?
                    customTextures[i] :
                    mesh->glTexture;

        //is equivalent to
        /*
        if (customTextures != NULL)
        {
                glTexture = customTextures[i];
        } else
        {

            glTexture = mesh->glTexture;

        }*/

        if (!shader->enableDepthTest) glDisable(GL_DEPTH_TEST);
        if (!shader->enableDepthMask) glDepthMask(GL_FALSE);



        //FIXME!!
        //"pose" operations to be added here.
        Matrix4::MultiplyMM(modelViewMatrix, 0,
                            lookAtMatrix, 0,
                            modelMatrix, 0);

        Matrix4::MultiplyMM(modelViewProjectionMatrix, 0,
                            projectionMatrix, 0,
                            modelViewMatrix, 0);


        if (naiveLastShader != shader) // Naïve optimisation attempt
        {
            naiveLastShader = shader;
            shader->Run(mesh, NULL, NULL, NULL, modelMatrix, modelViewProjectionMatrix, glTexture, extraColorForTexture);
        } else
        {
            shader->BindMatrices(modelMatrix, modelViewProjectionMatrix);
            if (glTexture != naiveLastTexture)
            {
                naiveLastTexture = glTexture;
                shader->BindTexture(glTexture);
            }
            shader->BindExtraColorForTexture(extraColorForTexture);
        }

        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dataGL->elementBuffersIDs[i]);

        // Draw the mesh!
        glDrawElements(
                    GL_TRIANGLES,      // mode
                    mesh->drawOrderCount,    // count
                    GL_UNSIGNED_SHORT,   // type
                    (void*)0           // element array buffer offset
                    );

        // Return toggles back to normal if they were changed
        if (!shader->enableDepthTest) glEnable(GL_DEPTH_TEST);
        if (!shader->enableDepthMask) glDepthMask(GL_TRUE);
    }

    // Reset GL states (should not be needed if everything is sane)
    /*
    glDisableVertexAttribArray(MJ_VERTEX_COORDINATES_GLVERTEXATTRIB_ID);
    glDisableVertexAttribArray(MJ_UV_COMPONENTS_GLVERTEXATTRIB_ID);
    glDisableVertexAttribArray(MJ_NORMAL_COORDINATES_GLVERTEXATTRIB_ID);
    */

}


void mjRendererGL::CleanForModel(mjModel &model)
{

}



}
