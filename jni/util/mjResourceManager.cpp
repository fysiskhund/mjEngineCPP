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
    mjResource* res = SearchByPath(models, path);
    if (res != NULL)
    {
        return ((mjModelResource*) res)->model;
    }

    mjModelResource* newResource = new mjModelResource();


    mjModel* newModel = new mjModel();
    newModel->LoadFromFile(path.c_str());

    newResource->model = newModel;
    newResource->path = path;
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
    mjResource* res = SearchByPath(textures, path);
    if (res != NULL)
    {
        return ((mjTextureResource*) res)->glResourceID;
    }

    mjTextureResource* newResource = new mjTextureResource();


    mjImageLoader loader;

    newResource->glResourceID = loader.LoadToGLAndFreeMemory(path.c_str());
    newResource->path = path;
    textures.push_back(newResource);


    return newResource->glResourceID;
}
mjResource* mjResourceManager::SearchByPath(std::vector<mjResource*>& repo, std::string& path)
{

    for(unsigned i = 0; i < repo.size(); i++)
    {
        mjResource* res = repo[i];
        if (res->path == path)
        {
            return res;
        }
    }

    return NULL;
}


}
