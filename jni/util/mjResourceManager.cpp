#include "mjResourceManager.h"

#ifdef IOS

// Note: in XCode this file is marked as Objective-C++ source to enable [NSStuff functionsAndEtc];
#import <Foundation/Foundation.h>
#import <Foundation/NSString.h>
#endif


namespace mjEngine{

mjResourceManager::mjResourceManager(std::string& pathPrefix, mjRenderer* renderer, AAssetManager* assMan, time_t* rngSeed)
{
    srand(time(rngSeed)); // Seed the RNG
    this->renderer = renderer;
    this->pathPrefix = pathPrefix;
    this->assMan = assMan;


    #ifdef WIN32
        separator = '\\';
    #else
        separator = '/';
    #endif // WIN32

    std::replace(this->pathPrefix.begin(), this->pathPrefix.end(), '/', separator);

    std::string shaderName = "default";
    PushShader(new mjDefaultShaders());
    LOGI("%s %d: new %s", __FILE__, __LINE__, "defaultShaders");

    shaderName = "skybox";
    PushShader(new mjSkyboxShaders());
    LOGI("%s %d: new %s", __FILE__, __LINE__, "skyboxShaders");


    shaderName = "text";
    PushShader(new mjTextShaders());
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
#ifdef ANDROID_ASSMAN
    fullPath = "mjEngineCPP/";
    fullPath += path;
#else
    PrependFullFilePath(fullPath);
#endif

    mjResource* res = SearchByPath(models, fullPath);
    if (res != NULL)
    {
        return ((mjModelResource*) res)->model;
    }

    mjModelResource* newResource = new mjModelResource();
    LOGI("%s %d: new %s", __FILE__, __LINE__, "modelResource");


    mjModel* newModel = new mjModel();
#ifdef ANDROID_ASSMAN

    mjFileFromArchive* mjFile;
    const unsigned char* modelData;
    size_t sizeRead;

    mjFile = ReadAllFromArchiveToBuffer(fullPath.c_str(), &modelData, &sizeRead);
    newModel->LoadFromMemory(modelData, sizeRead);
    CloseAndFreeResources(&mjFile);

#else
    const unsigned char* modelContents;
    size_t readSize;
    mjFileFromArchive* modelFile = ReadAllFromArchiveToBuffer(fullPath.c_str(), &modelContents, &readSize);
    newModel->LoadFromMemory(modelContents, readSize);
    CloseAndFreeResources(&modelFile);
#endif

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

#ifdef ANDROID_ASSMAN
    fullPath = "mjEngineCPP/";
    fullPath += path;
#else
    PrependFullFilePath(fullPath);
#endif

    mjResource* res = SearchByPath(textures, fullPath, glTextureWrapParameter);
    if (res != NULL)
    {
        return ((mjTextureResource*) res)->glResourceID;
    }

    mjTextureResource* newResource = new mjTextureResource();
    LOGI("%s %d: new %s", __FILE__, __LINE__, "textureResource");
    newResource->modifier = glTextureWrapParameter;

    mjImageLoader loader(ReadFromArchive);

    //LOGI("Texture's full path: %s", fullPath.c_str());
    unsigned const char* tmpBuffer;
    size_t readSize;
    newResource->mjFile = ReadAllFromArchiveToBuffer(fullPath.c_str(), &tmpBuffer, &readSize );



    newResource->glResourceID = loader.LoadToGLAndFreeMemory(newResource, glTextureWrapParameter);
    CloseAndFreeResources(&newResource->mjFile);

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
#ifdef ANDROID_ASSMAN
    fullPath = "mjEngineCPP/";
    fullPath += path;
#else
    PrependFullFilePath(fullPath);
#endif

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

#if !defined(ANDROID_ASSMAN) && !defined(IOS)
    // Load the buffer in all other platforms

    newResource->fileFromArchive = ReadAllFromArchiveToBuffer(fullPath.c_str(), &newResource->buffer, &newResource->bufferSize);
    // Leave soundFile open since we need the buffer to remain valid as well

#endif

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

mjShaderResource* mjResourceManager::PushShader(mjShader* shader)
{
    std::string shaderName = shader->name;

    mjShaderResource* result = (mjShaderResource*) SearchByPathIgnoreExtension(shaderResources, shaderName);

    if (result == NULL)
    {
        result = new mjShaderResource;
        LOGI("%s %d: new %s", __FILE__, __LINE__, "shaderResource");
        result->path = shaderName;
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

#ifdef ANDROID_ASSMAN
    fullPath = "mjEngineCPP/";
    fullPath += path;
#else
    PrependFullFilePath(fullPath);
#endif

    mjResource* res = SearchByPath(fontResources, fullPath);
    if (res != NULL)
    {
        return ((mjFontResource*) res);
    }

    mjFontResource* newResource = new mjFontResource();
    newResource->identifier = fontResources.size();

    LOGI("fetching font %s", fullPath.c_str());


    size_t readSize;
    const unsigned char* buffer;

    newResource->fontFile = ReadAllFromArchiveToBuffer(fullPath.c_str(), &buffer, &readSize);

    if (FT_New_Memory_Face(ft, buffer, readSize, 0, &newResource->face))
    {
        LOGI("Error while loading font %s.", fullPath.c_str());
    }
    // The buffer needs to remain valid until the font is no longer needed, hence not closing it now.


    FT_Select_Charmap(newResource->face, FT_ENCODING_UNICODE);

    LOGI("%s %d: new %s", __FILE__, __LINE__, "fontResource");

    //FT_Select_Charmap(newResource->face, FT_ENCODING_UNICODE);

    newResource->path = fullPath;
    fontResources.push_back(newResource);


    return newResource;


}


mjGraphicCharObjectResource* mjResourceManager::FetchGraphicChar(mjFontResource *fontResource, int fontSize, unsigned long charToRenderLong)
{
    // Max 100 different fonts at the same time due to lookup constraints.
    // But seriously who would use more than 100 fonts at the same time lol
    mjGraphicCharObjectResource* result = (mjGraphicCharObjectResource*) SearchByIdentifier(graphicCharObjectResources, charToRenderLong, (fontSize*100) + fontResource->identifier);

    if (result != NULL)
    {
        //LOGI("Reused 1 char [%lu] !", charToRenderLong);
        return result;
    } else
    {
        //LOGI("Rendering char [%lu]", charToRenderLong);
    }

    result = new mjGraphicCharObjectResource(fontResource, fontSize, charToRenderLong);

    result->identifier = charToRenderLong;
    result->modifier = (fontSize*100) + fontResource->identifier;

    graphicCharObjectResources.push_back(result);

    return result;

}

// Searches //

mjResource* mjResourceManager::SearchByPath(std::vector<mjResource*>& repo, std::string& fullPath, int modifier)
{

    for(unsigned i = 0; i < repo.size(); i++)
    {
        mjResource* res = repo[i];
        if ((res->path.compare(fullPath) == 0) && modifier == res->modifier)
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
        pathWithoutExtension = fullPath.substr(0, lastDotLocation);
    } else
    {
        pathWithoutExtension = fullPath;
    }


    for(unsigned i = 0; i < repo.size(); i++)
    {
        mjResource* res = repo[i];
        std::string otherPathWithoutExtension = res->path.c_str();


        lastDotLocation = otherPathWithoutExtension.find_last_of('.');

        if (lastDotLocation != std::string::npos)
        {
            otherPathWithoutExtension = otherPathWithoutExtension.substr(0, lastDotLocation);
        }

        if ((otherPathWithoutExtension.compare(pathWithoutExtension) == 0) && modifier == res->modifier)
        {
            return res;
        }
    }

    return NULL;
}

mjResource* mjResourceManager::SearchByIdentifier(std::vector<mjResource*>& repo, unsigned long identifier, int modifier)
{

    for(unsigned i = 0; i < repo.size(); i++)
    {
        mjResource* res = repo[i];

        if (identifier == res->identifier && modifier == res->modifier)
        {
            return res;
        }
    }

    return NULL;
}

//! Note: DO ___NOT___ try to free this buffer yourself. The system does it for you
mjFileFromArchive* mjResourceManager::ReadAllFromArchiveToBuffer(const char* filename, const unsigned char** buffer, size_t* readSize)
{
    mjFileFromArchive* mjFile = OpenFromArchive(filename, READ_MODE_READ_ALL);
    LOGI("ReadAllFromArchiveToBuffer: %s", filename);
#ifdef ANDROID_ASSMAN

    *buffer = (const unsigned char*) AAsset_getBuffer(mjFile->ass);
    *readSize = AAsset_getLength(mjFile->ass);
    LOGI("Read from archive[%s]: %u", filename, *readSize );
#else

    struct stat statData;
    stat(filename, &statData);
    mjFile->internalUseOnly_wholeFileBuffer = new unsigned char[statData.st_size];
    fread((void*) mjFile->internalUseOnly_wholeFileBuffer, statData.st_size, 1, mjFile->internalUseOnly_fileDescriptor);
    mjFile->internalUseOnly_wholeFileBufferSize = statData.st_size;

    *readSize = statData.st_size;
    *buffer = mjFile->internalUseOnly_wholeFileBuffer;


#endif

    return mjFile;
}

mjFileFromArchive* mjResourceManager::OpenFromArchive(const char* path, ArchiveReadMode readMode)
{
    mjFileFromArchive* mjFile = new mjFileFromArchive();
    LOGI("OpenFromArchive: %s", path);
#ifdef ANDROID_ASSMAN

    mjFile->ass = AAssetManager_open(assMan, path, AASSET_MODE_UNKNOWN);

    return mjFile;
#else
    mjFile->internalUseOnly_fileDescriptor = fopen(path, "rb");
#endif
    
#ifdef IOS
    mjFile->iosOnly_fullPath = path;
#endif


    return mjFile;
}

size_t mjResourceManager::ReadFromArchive(mjFileFromArchive* mjFile, const unsigned char* buffer, size_t howMany)
{
    //LOGI("Attempting to read %u bytes", howMany);
#ifdef ANDROID_ASSMAN
    return AAsset_read(mjFile->ass, (void*) buffer, howMany);
#else
    return fread((void *)buffer, howMany, 1, mjFile->internalUseOnly_fileDescriptor);
#endif

}

void mjResourceManager::CloseAndFreeResources(mjFileFromArchive** mjFile)
{
#ifdef ANDROID_ASSMAN
    AAsset_close((*mjFile)->ass);
#endif


    delete *mjFile;
    *mjFile = NULL; // Mark as no longer usable.

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
