#include "mjResourceManager.h"
namespace mjEngine{

mjResourceManager::mjResourceManager(std::string& pathPrefix)
{
    this->pathPrefix = pathPrefix;
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
    std::string fullPath = pathPrefix + "/" + path;

    mjResource* res = SearchByPath(models, fullPath);
    if (res != NULL)
    {
        return ((mjModelResource*) res)->model;
    }

    mjModelResource* newResource = new mjModelResource();


    mjModel* newModel = new mjModel();
    newModel->LoadFromFile(fullPath.c_str());

    newResource->model = newModel;
    newResource->path = fullPath;
    models.push_back(newResource);


    return newModel;


}

GLuint mjResourceManager::FetchTexture(const char* path)
{
    std::string pathStr = path;
    return FetchTexture(pathStr);
}

GLuint mjResourceManager::FetchTexture(std::string& path)
{
    std::string fullPath = pathPrefix + "/" + path;

    mjResource* res = SearchByPath(textures, fullPath);
    if (res != NULL)
    {
        return ((mjTextureResource*) res)->glResourceID;
    }

    mjTextureResource* newResource = new mjTextureResource();


    mjImageLoader loader;
    //LOGI("Texture's full path: %s", fullPath.c_str());
    newResource->glResourceID = loader.LoadToGLAndFreeMemory(fullPath.c_str());
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
    std::string fullPath = pathPrefix + "/" + path;

    mjResource* res = SearchByPath(modelStructures, fullPath);
    if (res != NULL)
    {
        return ((mjModelStructureResource*) res)->structure;
    }

    mjModelStructureResource* newResource = new mjModelStructureResource();

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
    std::string fullPath = pathPrefix + "/" + path;

    mjResource* res = SearchByPath(soundResources, fullPath);
    if (res != NULL)
    {
        return ((mjSoundResource*) res);
    }

    mjSoundResource* newResource = new mjSoundResource();


    newResource->soundIndexAndroid = this->soundIndexAndroid;

    this->soundIndexAndroid++;

    newResource->path = fullPath;
    soundResources.push_back(newResource);

    return newResource;
}




mjResource* mjResourceManager::SearchByPath(std::vector<mjResource*>& repo, std::string& fullPath)
{

    for(unsigned i = 0; i < repo.size(); i++)
    {
        mjResource* res = repo[i];
        if (res->path == fullPath)
        {
            return res;
        }
    }

    return NULL;
}




}
