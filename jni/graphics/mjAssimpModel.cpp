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
                    texFilenameWithoutJunk = texFilenameWithoutJunk.substr(lastDirChar+1);
                    glTextureForMaterial.push_back(resManager->FetchTexture(texFilenameWithoutJunk, GL_REPEAT));
                }
            }
            diffuseTextureIndex++;
        } while (textureFilenameWasExtracted == AI_SUCCESS);

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
        float* modelMatrix, float* lookAtMatrix, float* modelViewMatrix, float* projectionMatrix, float* modelViewProjectionMatrix)
{
    float poseMatrix[16];
    float tempMatrix[16];
    float matrixAfterStack[16];
    float* whichMatrix;


    aiNode* node = scene->mRootNode;

    //Matrix4::DebugM("mvp", modelViewProjectionMatrix);

    RecursiveDraw(shaderList, modelMatrix, lookAtMatrix, modelViewMatrix, projectionMatrix, modelViewProjectionMatrix, node);


}

void mjAssimpModel::RecursiveDraw(std::vector<mjShader*>& shaderList, float* modelMatrix, float* lookAtMatrix, float* modelViewMatrix, float* projectionMatrix, float* modelViewProjectionMatrix, aiNode *node)
{
    for(unsigned i = 0; i < node->mNumMeshes; i++)
    {
        const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; // From the scene, fetch the mesh that is in use by the current node.
        if (0)
        {


            /*mjVector3 testPos;
            mjVector3 angles;
            angles.CopyFrom(*pose->angles[i]);
            testPos.CopyFrom(*pose->positions[i]);

            Matrix4::GetPositionScaleAndAngleRotationMatrix(testPos, angles, poseMatrix);//(*pose->positions[i], *pose->angles[i], poseMatrix);
            Matrix4::MultiplyMM(tempMatrix, 0,
                    modelMatrix, 0,
                    poseMatrix, 0);

            Matrix4::MultiplyMM(modelViewMatrix, 0,
                    lookAtMatrix, 0,
                    tempMatrix, 0);
            //Matrix4::MultiplyMM(modelViewMatrix, 0, )
            */
        } else
        {
            Matrix4::MultiplyMM(modelViewMatrix, 0,
                    lookAtMatrix, 0,
                    modelMatrix, 0);
        }
        Matrix4::MultiplyMM(modelViewProjectionMatrix, 0,
                projectionMatrix, 0,
                modelViewMatrix, 0);

        // FIXME: find a way to tie the shaders from normal models with assimp-loaded models.
        // For now, the default shader is used.
        shaderList[0]->RunForAssimp(mesh,
                0, 0, 0,
                modelMatrix, modelViewProjectionMatrix, glTextureForMaterial[mesh->mMaterialIndex]);

        glDrawElements(GL_TRIANGLES, mesh->mFaces->mNumIndices, GL_UNSIGNED_SHORT, mesh->mFaces->mIndices);
    }

    // honey I unrolled the children
    for (int n = 0; n < node->mNumChildren; n++)
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
