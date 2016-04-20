#include "mjAssimpModel.h"



namespace mjEngine{

mjAssimpModel::mjAssimpModel(mjResourceManager* resManager)
{
    this->resManager = resManager;

#ifdef OSX
    // Generate the buffers needed for CORE profile compliance
    glGenVertexArraysAPPLE(1, &vertexArrayObject);
    glGenBuffers(3, objectBuffers);
#endif


}

void mjAssimpModel::LoadFromFile(const char* fileName)
{
    scene = aiImportFile(fileName,aiProcessPreset_TargetRealtime_MaxQuality);

    for (int i = 0; i < scene->mNumMaterials; i++)
    {
        // Keep trying to extract textures until it fails
        aiString textureFilename;

        aiMaterial* mat = scene->mMaterials[i];

        aiReturn textureFilenameWasExtracted;
        int diffuseTextureIndex = 0;

        do
        {
            textureFilenameWasExtracted = mat->GetTexture(aiTextureType_DIFFUSE, diffuseTextureIndex, &textureFilename);
            if (textureFilenameWasExtracted == AI_SUCCESS)
            {
                // Load using the manager.

                //FIXME: For now only the first texture is used :3

                if (diffuseTextureIndex == 0)
                {
                    std::string texFilenameWithoutJunk = textureFilename.C_Str();
                    int lastDirChar = texFilenameWithoutJunk.find_last_of('/');
                    int lastInvertDirChar = texFilenameWithoutJunk.find_last_of('\\');
                    if (lastInvertDirChar > lastDirChar)
                    {
                        lastDirChar = lastInvertDirChar;
                    }
                    texFilenameWithoutJunk = texFilenameWithoutJunk.substr(lastDirChar+1);
                    glTextureForMaterial.push_back(resManager->FetchTexture(texFilenameWithoutJunk, GL_REPEAT));
                }
            }
            diffuseTextureIndex++;
        } while (textureFilenameWasExtracted == AI_SUCCESS);

    }


    // Now build the internal data structures ( structure, drawOrderBuffers, etc.)


    for (unsigned i = 0; i < scene->mNumMeshes; i++)
    {
        meshes.push_back(NULL);
    }



    aiNode* node = scene->mRootNode;


    RecursiveBuild(node);

}

void mjAssimpModel::RecursiveBuild(aiNode* node)
{



    for(unsigned i = 0; i < node->mNumMeshes; i++)
    {
        const aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]]; // From the scene, fetch the mesh that is in use by the current node.
        if (meshes[node->mMeshes[i]] == NULL)
        {
            mjModelMesh* mjMesh = new mjModelMesh();

            meshes[node->mMeshes[i]] = mjMesh;

            mjMesh->drawOrderCount = 3*assimpMesh->mNumFaces;

            mjMesh->drawOrderBuffer = new unsigned short[mjMesh->drawOrderCount];

            mjMesh->vertexBuffer = new float[assimpMesh->mNumFaces*3*3]; // *3 because triangle, *3 because xyz

            mjMesh->normalBuffer = new float[assimpMesh->mNumFaces*3*3]; // *3 because triangle, *3 because xyz

            mjMesh->textureCoordsBuffer = new float[assimpMesh->mNumFaces*3*2]; // *3 because triangle, *3 because uv





            unsigned drawOrderIndex = 0;
            for (unsigned f = 0; f < assimpMesh->mNumFaces; f++)
            {
                aiFace* face =  &assimpMesh->mFaces[f];

                for (unsigned vIndex = 0; vIndex < assimpMesh->mNumVertices; vIndex++)
                {
                    mjMesh->vertexBuffer[0 + (vIndex*3)] = assimpMesh->mVertices[vIndex].x;
                    mjMesh->vertexBuffer[1 + (vIndex*3)] = assimpMesh->mVertices[vIndex].y;
                    mjMesh->vertexBuffer[2 + (vIndex*3)] = assimpMesh->mVertices[vIndex].z;

                    mjMesh->normalBuffer[0 + (vIndex*3)] = assimpMesh->mNormals[vIndex].x;
                    mjMesh->normalBuffer[1 + (vIndex*3)] = assimpMesh->mNormals[vIndex].y;
                    mjMesh->normalBuffer[2 + (vIndex*3)] = assimpMesh->mNormals[vIndex].z;

                    float texCoord = assimpMesh->mTextureCoords[0][vIndex].x;
                    mjMesh->textureCoordsBuffer[0 + (vIndex*2)] = texCoord;

                    texCoord = assimpMesh->mTextureCoords[0][vIndex].y;
                    mjMesh->textureCoordsBuffer[1 + (vIndex*2)] = 1-texCoord;
                }

                for (unsigned vIndex = 0; vIndex < face->mNumIndices; vIndex++)
                {
                    mjMesh->drawOrderBuffer[drawOrderIndex] = face->mIndices[vIndex];

                    /*unsigned vertexIndex = face->mIndices[vIndex];
                    mjMesh->vertexBuffer[0 + (drawOrderIndex*3)] = assimpMesh->mVertices[vertexIndex].x;
                    mjMesh->vertexBuffer[1 + (drawOrderIndex*3)] = assimpMesh->mVertices[vertexIndex].y;
                    mjMesh->vertexBuffer[2 + (drawOrderIndex*3)] = assimpMesh->mVertices[vertexIndex].z;

                    LOGI("drawOrder[%d]: %3.1f, %3.1f, %3.1f", mjMesh->vertexBuffer[0 + (drawOrderIndex*3)], mjMesh->vertexBuffer[1 + (drawOrderIndex*3)], mjMesh->vertexBuffer[2 + (drawOrderIndex*3)]);

                    mjMesh->normalBuffer[0 + (drawOrderIndex*3)] = assimpMesh->mNormals[vertexIndex].x;
                    mjMesh->normalBuffer[1 + (drawOrderIndex*3)] = assimpMesh->mNormals[vertexIndex].y;
                    mjMesh->normalBuffer[2 + (drawOrderIndex*3)] = assimpMesh->mNormals[vertexIndex].z;

                    float texCoord = assimpMesh->mTextureCoords[0][vertexIndex].x;
                    mjMesh->textureCoordsBuffer[0 + (drawOrderIndex*2)] = texCoord;

                    texCoord = assimpMesh->mTextureCoords[0][vertexIndex].y;
                    mjMesh->textureCoordsBuffer[1 + (drawOrderIndex*2)] = texCoord;*/



                    drawOrderIndex++;



                }
            }

            LOGI("Mesh %d has %d vertices   ", i, assimpMesh->mNumVertices);
        }
        //glDrawElements(GL_TRIANGLES, mesh->, GL_UNSIGNED_SHORT, mesh->mFaces->mIndices);
        checkGlError("afterDrawElements");
    }

    // honey I unrolled the children
    for (unsigned int n = 0; n < node->mNumChildren; n++)
    {
        RecursiveBuild(node->mChildren[n]);
    }
}



void mjAssimpModel::TieShaders(std::vector<mjShader*>& shaderList)
{
/*
    for(unsigned i = 0; i < meshes.size(); i++)
    {
        if (meshes[i]->shaderName == NULL)
        {
            //LOGI("Mesh %s: Default shader attached", meshes[i]->name);
            meshes[i]->mjShaderListIndex = 0; // 0 will always be the default shader.
        } else
        {
            for (unsigned j = 0; j < shaderList.size(); j++)
            {
                //LOGI("Considering shader %s", shaderList[j]->name);
                if (strncmp(meshes[i]->shaderName, shaderList[j]->name, 96) == 0)
                {
                    //LOGI("Mesh %s: %s shader attached",meshes[i]->name, shaderList[j]->name);
                    meshes[i]->mjShaderListIndex = j;
                }
            }
            if (meshes[i]->mjShaderListIndex == 0)
            {
                LOGI("Mesh %s: %s shader not found", meshes[i]->name, meshes[i]->shaderName);
            }
        }
    }
    */
}


#if defined(USE_GLES2) || defined(USE_GL3)
// Drawing routine for OpenGL ES 2.0 & OpenGL 3

void mjAssimpModel::Draw(std::vector<mjShader*>& shaderList,
                         GLfloat* modelMatrix, GLfloat* lookAtMatrix, GLfloat* modelViewMatrix, GLfloat* projectionMatrix, GLfloat* modelViewProjectionMatrix, mjModelPose* pose)
{
    float poseMatrix[16];
    float tempMatrix[16];
    float matrixAfterStack[16];
    float* whichMatrix;


    aiNode* node = scene->mRootNode;

    //Matrix4::DebugM("mvp", modelViewProjectionMatrix);
    //



    Matrix4::MultiplyMM(modelViewMatrix, 0,
            lookAtMatrix, 0,
            modelMatrix, 0);

    Matrix4::MultiplyMM(modelViewProjectionMatrix, 0,
            projectionMatrix, 0,
            modelViewMatrix, 0);

    RecursiveDraw(shaderList, modelMatrix, lookAtMatrix, modelViewMatrix, projectionMatrix, modelViewProjectionMatrix, node);


}

void mjAssimpModel::RecursiveDraw(std::vector<mjShader*>& shaderList, float* modelMatrix, float* lookAtMatrix, float* modelViewMatrix, float* projectionMatrix, float* modelViewProjectionMatrix, aiNode *node)
{


    /*if (node == scene->mRootNode)
    {
        LOGI("Root");
    }*/

    for(unsigned i = 0; i < node->mNumMeshes; i++)
    {
        const aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]]; // From the scene, fetch the mesh that is in use by the current node.

        mjModelMesh* mjMesh = meshes[node->mMeshes[i]];

        // FIXME: find a way to tie the shaders from normal models with assimp-loaded models.
        // For now, the default shader is used.
        shaderList[0]->Run(mjMesh, mjMesh->vertexBuffer, mjMesh->textureCoordsBuffer, mjMesh->normalBuffer,
                                    modelMatrix, modelViewProjectionMatrix, glTextureForMaterial[assimpMesh->mMaterialIndex]);
        //LOGI("Mesh %d has %d vertices   ", i, mesh->mNumVertices);
        glDrawElements(GL_TRIANGLES, mjMesh->drawOrderCount, GL_UNSIGNED_SHORT, mjMesh->drawOrderBuffer);
        checkGlError("afterDrawElements");
    }

    // honey I unrolled the children
    for (unsigned int n = 0; n < node->mNumChildren; n++)
    {
        RecursiveDraw(shaderList, modelMatrix, lookAtMatrix, modelViewMatrix, projectionMatrix, modelViewProjectionMatrix, node->mChildren[n]);
    }

}



#elif USE_NULL_RENDERER
void mjModel::Draw(std::vector<mjShader*>& shaderList,
    float* modelMatrix, float* lookAtMatrix, float* modelViewMatrix, float* projectionMatrix, float* modelViewProjectionMatrix, mjModelPose* pose)
{
    // Nothing is rendered, this is useful for the dedicated-server version of the games
}
#else
    #error "No rendering system is defined. Choose USE_GLES2, USE_GL3 or USE_NULL_RENDERER"
#endif

}// namespace mj
