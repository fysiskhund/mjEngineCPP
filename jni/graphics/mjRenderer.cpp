#include "mjRenderer.h"

namespace mjEngine
{

mjRenderer::mjRenderer()
{

}

void mjRenderer::PrepareForModel(mjModel& model)
{

    checkGlError("starting with PrepareForModel");
#ifndef USE_GLES2
    glGenVertexArrays(1, vertexArrayID);
    checkGlError("creating VAO");
    glBindVertexArray(vertexArrayID[0]);
    checkGlError("binding newly created VAO");
#endif
    shader = new mjDefaultShaders();

    checkGlError("defining Shader");
    // shader has glProgramID and all other handles

    glGenBuffers(1, &vertexCoordinatesBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexCoordinatesBufferID);
    glBufferData(GL_ARRAY_BUFFER, model.numVertices * sizeof(GLfloat)*3, model.vertexBufferData, GL_STATIC_DRAW);

    glGenBuffers(1, &uvComponentsBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, uvComponentsBufferID);
    glBufferData(GL_ARRAY_BUFFER, model.numVertices * sizeof(GLfloat)*2, model.texCoordBufferData, GL_STATIC_DRAW);

    glGenBuffers(1, &normalCoordinatesID);
    glBindBuffer(GL_ARRAY_BUFFER, normalCoordinatesID);
    glBufferData(GL_ARRAY_BUFFER, model.numVertices * sizeof(GLfloat)*3, model.normalComponentBufferData, GL_STATIC_DRAW);

    LOGI("Created buffers- VAO %d;  vertexC %d;  uvC %d;  norC %d\n", vertexArrayID[0], vertexCoordinatesBufferID, uvComponentsBufferID, normalCoordinatesID);

    checkGlError("defining buffers");

    // Generate a buffer for the indices as well
    elementBuffersIDs = new GLuint[model.meshes.size()];
    glGenBuffers(model.meshes.size(), elementBuffersIDs);
    for (uint16_t i = 0; i < model.meshes.size(); i++)
    {
        mjModelMesh* mesh = model.meshes[i];
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffersIDs[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->drawOrderCount * sizeof(unsigned short), mesh->drawOrderBuffer , GL_STATIC_DRAW);
    }
    checkGlError("defining element buffers");

}

void mjRenderer::RenderModel(mjModel& model, float* modelMatrix, float* lookAtMatrix, float* projectionMatrix, mjModelPose* pose, mjMatrixStack* stack)
{
    float modelViewMatrix[16];
    float modelViewProjectionMatrix[16];

#ifndef USE_GLES2
    glBindVertexArray(vertexArrayID[0]);
#endif

    glEnableVertexAttribArray(MJ_VERTEX_COORDINATES_GLVERTEXATTRIB_ID); // Tell OpenGL we will use the slot 0, which we arbitrarily defined as vertex coordinate buffer when the shader source codes were loaded
    glBindBuffer(GL_ARRAY_BUFFER, vertexCoordinatesBufferID);
    glVertexAttribPointer(MJ_VERTEX_COORDINATES_GLVERTEXATTRIB_ID, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // vertexBuffer); // According to da internetz, when using VAOs, the last parameter becomes an offset and not a memory address

    glEnableVertexAttribArray(MJ_UV_COMPONENTS_GLVERTEXATTRIB_ID); // Tell OpenGL we will use the slot 1, which we arbitrarily defined as UV components when the shader source codes were loaded
    glBindBuffer(GL_ARRAY_BUFFER, uvComponentsBufferID);
    glVertexAttribPointer(MJ_UV_COMPONENTS_GLVERTEXATTRIB_ID, 2, GL_FLOAT, GL_FALSE, 0, nullptr); // texCoordBuffer); // According to da internetz, when using VAOs, the last parameter becomes an offset and not a memory address

    glEnableVertexAttribArray(MJ_NORMAL_COORDINATES_GLVERTEXATTRIB_ID); // Tell OpenGL we will use the slot 2, which we arbitrarily defined as the coordinates of the normals when the shader source codes were loaded
    glBindBuffer(GL_ARRAY_BUFFER, normalCoordinatesID);
    glVertexAttribPointer(MJ_NORMAL_COORDINATES_GLVERTEXATTRIB_ID, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // normalComponentBuffer); // According to da internetz, when using VAOs, the last parameter becomes an offset and not a memory address

    checkGlError("After binding Vertex Array Pointers");
    
    for (uint16_t i = 0; i < model.meshes.size(); i++)
    {
        //FIXME!!
        //"pose" operations to be added here.
       Matrix4::MultiplyMM(modelViewMatrix, 0,
            lookAtMatrix, 0,
            modelMatrix, 0);

        Matrix4::MultiplyMM(modelViewProjectionMatrix, 0,
            projectionMatrix, 0,
            modelViewMatrix, 0);

        mjModelMesh* mesh = model.meshes[i];

        shader->Run(mesh, NULL, NULL, NULL, modelMatrix, modelViewProjectionMatrix, mesh->glTexture);

        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffersIDs[i]);

        // Draw the mesh!
        glDrawElements(
            GL_TRIANGLES,      // mode
            mesh->drawOrderCount,    // count
            GL_UNSIGNED_SHORT,   // type
            (void*)0           // element array buffer offset
        );
    }
            glDisableVertexAttribArray(MJ_VERTEX_COORDINATES_GLVERTEXATTRIB_ID);
            glDisableVertexAttribArray(MJ_UV_COMPONENTS_GLVERTEXATTRIB_ID);
            glDisableVertexAttribArray(MJ_NORMAL_COORDINATES_GLVERTEXATTRIB_ID);

}

void  mjRenderer::CleanForModel(mjModel& model)
{

}

void mjRenderer::RenderMesh(mjModelMesh& mesh)
{

}

}
