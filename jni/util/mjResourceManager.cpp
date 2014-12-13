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

    newResource->glResourceID = loader.LoadToGLAndFreeMemory(fullPath.c_str());
    newResource->path = fullPath;
    textures.push_back(newResource);


    return newResource->glResourceID;
}

mjModelPose* mjResourceManager::FetchPose(const char* path)
{
    std::string pathStr = path;
    return FetchPose(pathStr);
}

mjModelPose* mjResourceManager::FetchPose(std::string& path)
{
    std::string fullPath = pathPrefix + "/" + path;

    mjResource* res = SearchByPath(textures, fullPath);
    if (res != NULL)
    {
        return ((mjPoseResource*) res)->pose;
    }

    mjPoseResource* newResource = new mjPoseResource(fullPath.c_str());


    newResource->path = fullPath;
    poses.push_back(newResource);


    return newResource->pose;
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
