#include "mjResourceManager.h"

#ifdef IOS

// Note: in XCode this file is marked as Objective-C++ source to enable [NSStuff functionsAndEtc];
#import <Foundation/Foundation.h>
#import <Foundation/NSString.h>
#endif


namespace mjEngine{

mjResourceManager::mjResourceManager(std::string& pathPrefix)
{
    this->pathPrefix = pathPrefix;
    #ifdef WIN32
        separator = '\\';
    #else
        separator = '/';
    #endif // WIN32

    std::replace(this->pathPrefix.begin(), this->pathPrefix.end(), '/', separator);
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


    mjModel* newModel = new mjModel();
    newModel->LoadFromFile(fullPath.c_str());

    newResource->model = newModel;
    newResource->path = fullPath;
    models.push_back(newResource);


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


    newResource->soundIndexAndroid = this->soundIndexAndroid;

    this->soundIndexAndroid++;

    newResource->path = fullPath;
    soundResources.push_back(newResource);

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
