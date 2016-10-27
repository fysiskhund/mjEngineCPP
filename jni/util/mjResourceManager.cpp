#include "mjResourceManager.h"

#ifdef IOS

// Note: in XCode this file is marked as Objective-C++ source to enable [NSStuff functionsAndEtc];
#import <Foundation/Foundation.h>
#import <Foundation/NSString.h>
#endif


namespace mjEngine{

mjResourceManager::mjResourceManager(std::string& pathPrefix, mjRenderer* renderer)
{
    this->renderer = renderer;
    this->pathPrefix = pathPrefix;
    #ifdef WIN32
        separator = '\\';
    #else
        separator = '/';
    #endif // WIN32

    std::replace(this->pathPrefix.begin(), this->pathPrefix.end(), '/', separator);

    std::string shaderName = "default";
    PushShader(shaderName, new mjDefaultShaders());
    LOGI("%s %d: new %s", __FILE__, __LINE__, "defaultShaders");

    shaderName = "skybox";
    PushShader(shaderName, new mjSkyboxShaders());
    LOGI("%s %d: new %s", __FILE__, __LINE__, "skyboxShaders");


    shaderName = "text";
    PushShader(shaderName, new mjTextShaders());
    LOGI("%s %d: new %s", __FILE__, __LINE__, "textShaders");



    if (FT_Init_FreeType(&ft))
    {
        LOGI("Error while initialising FreeType");
    } else
    {
        LOGI("FreeType initialised.");
    }


}

mjResourceManager::~mjResourceManager()
{
    //dtor
}
mjModel* mjResourceManager::FetchModel(const char* path)
{
    std::string pathStr = path;
    return FetchModel(pathStr);
}

mjModel* mjResourceManager::FetchModel(std::string& path)
{
    std::string fullPath = path;
    PrependFullFilePath(fullPath);

    mjResource* res = SearchByPath(models, fullPath);
    if (res != NULL)
    {
        return ((mjModelResource*) res)->model;
    }

    mjModelResource* newResource = new mjModelResource();
    LOGI("%s %d: new %s", __FILE__, __LINE__, "modelResource");


    mjModel* newModel = new mjModel();
    newModel->LoadFromFile(fullPath.c_str());
    LOGI("%s %d: new %s", __FILE__, __LINE__, "model");

    newResource->model = newModel;
    newResource->path = fullPath;
    models.push_back(newResource);


    // Tie the shaders to the meshes
    for (uint16_t i = 0; i < newModel->meshes.size(); i++)
    {
        mjModelMesh* mesh = newModel->meshes[i];
        if (mesh->mjShaderListIndex == -1)
        {
            mesh->mjShaderListIndex = this->FetchShader(mesh->shaderName)->shaderListIndex;
        }
    }

    // And finally, get the renderer to do the model preparations
    renderer->PrepareModel(*newModel);

    return newModel;


}

GLuint mjResourceManager::FetchTexture(const char* path, unsigned glTextureWrapParameter)
{
    std::string pathStr = path;
    return FetchTexture(pathStr, glTextureWrapParameter);
}

GLuint mjResourceManager::FetchTexture(std::string& path, unsigned glTextureWrapParameter)
{
    std::string fullPath = path;
    PrependFullFilePath(fullPath);

    mjResource* res = SearchByPath(textures, fullPath, glTextureWrapParameter);
    if (res != NULL)
    {
        return ((mjTextureResource*) res)->glResourceID;
    }

    mjTextureResource* newResource = new mjTextureResource();
    LOGI("%s %d: new %s", __FILE__, __LINE__, "textureResource");
    newResource->modifier = glTextureWrapParameter;


    mjImageLoader loader;
    //LOGI("Texture's full path: %s", fullPath.c_str());
    newResource->glResourceID = loader.LoadToGLAndFreeMemory(fullPath.c_str(), glTextureWrapParameter);
    newResource->path = fullPath;
    textures.push_back(newResource);


    return newResource->glResourceID;
}

mjModelStructure* mjResourceManager::FetchModelStructure(const char* path)
{
    std::string pathStr = path;
    return FetchModelStructure(pathStr);
}

mjModelStructure* mjResourceManager::FetchModelStructure(std::string& path)
{
    std::string fullPath = path;
    PrependFullFilePath(fullPath);

    mjResource* res = SearchByPath(modelStructures, fullPath);
    if (res != NULL)
    {
        return ((mjModelStructureResource*) res)->structure;
    }

    mjModelStructureResource* newResource = new mjModelStructureResource();
    LOGI("%s %d: new %s", __FILE__, __LINE__, "modelStructure");

    newResource->structure = new mjModelStructure(fullPath.c_str());

    newResource->path = fullPath;
    modelStructures.push_back(newResource);


    return newResource->structure;
}

mjSoundResource* mjResourceManager::FetchSound(const char* path)
{
    std::string pathStr = path;
    return FetchSound(pathStr);
}

mjSoundResource* mjResourceManager::FetchSound(std::string& path)
{
    std::string fullPath = path;
    PrependFullFilePath(fullPath);

    mjResource* res = SearchByPath(soundResources, fullPath);
    if (res != NULL)
    {
        return ((mjSoundResource*) res);
    }

    mjSoundResource* newResource = new mjSoundResource();
    LOGI("%s %d: new %s", __FILE__, __LINE__, "soundResource");


    newResource->soundIndexAndroid = this->soundIndexAndroid;

    this->soundIndexAndroid++;

    newResource->path = fullPath;
    soundResources.push_back(newResource);

    return newResource;
}

mjShaderResource* mjResourceManager::FetchShader(const char* name)
{
    std::string pathStr;
    if (name == NULL)
    {
        pathStr = "";
    } else
    {
        pathStr = name;
    }
    return FetchShader(pathStr);
}

mjShaderResource* mjResourceManager::FetchShader(std::string& name)
{
    if (name.empty())
    {
        name = "default";
    }
    std::string fullPath = name;
    // PrependFullFilePath(fullPath); // For now the shaders need to be loaded already.
    // At some point there will be the possibility to load them from text files.

    mjResource* res = SearchByPathIgnoreExtension(shaderResources, fullPath);
    if (res != NULL)
    {
        return ((mjShaderResource*) res);
    }

    // Load the shader sources

    // FIXME!! to be implemented actual file loading. And how this should work with shaders "pushed".
    // And do it in a way that is not problematic for (im)possible Vulkan/Metal integration in the future
    return NULL;
}

/*mjShaderResource* mjResourceManager::PushShader(std::string& name, std::string& vertexShader, std::string& fragmentShader)
{

    mjShaderResource* result = (mjShaderResource*) SearchByPathIgnoreExtension(shaderResources, name);

    if (result == NULL)
    {

        mjShader* shader = new mjShader();
        shader->CreateProgram(vertexShader.c_str(), fragmentShader.c_str());
        result = PushShader(name, shader);
    }

    return result;
}*/

mjShaderResource* mjResourceManager::PushShader(std::string& name, mjShader* shader)
{
    mjShaderResource* result = (mjShaderResource*) SearchByPathIgnoreExtension(shaderResources, name);

    if (result == NULL)
    {
        result = new mjShaderResource;
        LOGI("%s %d: new %s", __FILE__, __LINE__, "shaderResource");
        result->path = name;
        result->shader = shader;
        result->shaderListIndex = shaderList.size();

        shaderList.push_back(shader);
        shaderResources.push_back(result);

    }

    return result;
}

mjFontResource* mjResourceManager::FetchFont(std::string &path)
{

    std::string fullPath = path;
    PrependFullFilePath(fullPath);

    mjResource* res = SearchByPathIgnoreExtension(fontResources, fullPath);
    if (res != NULL)
    {
        return ((mjFontResource*) res);
    }

    mjFontResource* newResource = new mjFontResource();

    if (FT_New_Face(ft, fullPath.c_str(), 0, &newResource->face))
    {
        LOGI("Error while loading font %s.", fullPath.c_str());
    }


    LOGI("%s %d: new %s", __FILE__, __LINE__, "fontResource");

    //FT_Select_Charmap(newResource->face, FT_ENCODING_UNICODE);

    newResource->path = fullPath;
    fontResources.push_back(newResource);


    return newResource;


}




mjResource* mjResourceManager::SearchByPath(std::vector<mjResource*>& repo, std::string& fullPath, int modifier)
{

    for(unsigned i = 0; i < repo.size(); i++)
    {
        mjResource* res = repo[i];
        if (res->path == fullPath && modifier == res->modifier)
        {
            return res;
        }
    }

    return NULL;
}

mjResource* mjResourceManager::SearchByPathIgnoreExtension(std::vector<mjResource*>& repo, std::string& fullPath, int modifier)
{

    std::string pathWithoutExtension;

    int lastDotLocation = fullPath.find_last_of('.');

    if (lastDotLocation != std::string::npos)
    {
        pathWithoutExtension = fullPath.substr(0, lastDotLocation-1);
    } else
    {
        pathWithoutExtension = fullPath;
    }


    for(unsigned i = 0; i < repo.size(); i++)
    {
        mjResource* res = repo[i];
        if (res->path == pathWithoutExtension && modifier == res->modifier)
        {
            return res;
        }
    }

    return NULL;
}

#ifndef IOS

void mjResourceManager::PrependFullFilePath(std::string& filePath)
{
    filePath = pathPrefix + separator + filePath;
    std::replace(filePath.begin(), filePath.end(), '/', separator);
}

#else
    void mjResourceManager::PrependFullFilePath(std::string& filePath)
    {
        filePath = pathPrefix + separator + filePath;
        
        std::replace(filePath.begin(), filePath.end(), '/', separator);
        
        // Auto ogg -> mp3
        if (filePath.find(".ogg") == filePath.length()-4)
        {
            LOGI("iOS note: Searching for .mp3 instead of .ogg");
            filePath = filePath.substr(0,filePath.length()-4) + ".mp3";
        }
        
        NSString* resourcePath = [NSString stringWithUTF8String:filePath.c_str()];
        
        NSString* found = [[NSBundle mainBundle] pathForResource:resourcePath ofType:nil];
        
        if (found == nil)
        {
            std::string notFound = "Error: file [" + filePath + "] not found!";
            LOGI("%s", notFound.c_str());
            filePath = notFound;
        } else
        {
        
            filePath = [found UTF8String];
        }
        
    }
    
#endif



}
