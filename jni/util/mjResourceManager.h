#ifndef MJRESOURCEMANAGER_H
#define MJRESOURCEMANAGER_H

#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <sys/stat.h>

#include "../extLibs/tinyxml/tinyxml2.h"

#include "../graphics/mjModel.h"
#include "../graphics/mjImageLoader.h"
#include "../graphics/animation/mjModelStructure.h"
#include "mjModelResource.h"
#include "mjTextureResource.h"
#include "mjModelStructureResource.h"
#include "mjSoundResource.h"
#include "mjShaderResource.h"
#include "mjFontResource.h"
#include "mjGraphicCharObjectResource.h"
#include "mjPlatformInfoResource.h"

#include "graphics/mjShader.h"
#include "graphics/mjDefaultShaders.h"
#include "graphics/mjSkyboxShaders.h"
#include "graphics/renderer/mjRenderer.h"

#include "mjFileFromArchive.h"




#include "../text/mjTextShaders.h"




namespace mjEngine{

enum ArchiveReadMode{
    READ_MODE_NO_ASSUMPTIONS,
    READ_MODE_READ_ALL
};

class mjResourceManager
{
    public:

        std::vector<mjShader*> shaderList;
        AAssetManager* assMan;

        // Device & other info
        mjPlatformInfoResource platformInfo;

        mjResourceManager(std::string& pathPrefix, mjRenderer* renderer, AAssetManager* assMan,
                          MJ_PLATFORMTYPE platformType,
                          int screenWidth_px, int screenHeight_px,
                          float ppi_x, float ppi_y,
                          float screenWidth_cm, float screenHeight_cm,
                          MJ_SCREENSIZE screenSize,
                          time_t* rngSeed = 0);
    
        ~mjResourceManager();

        mjModel* FetchModel(const char* path);
        mjModel* FetchModel(std::string& path);

        GLuint FetchTexture(const char* path, unsigned glTextureWrapParameter = GL_CLAMP_TO_EDGE);
        GLuint FetchTexture(std::string& path, unsigned glTextureWrapParameter = GL_CLAMP_TO_EDGE);

        mjModelStructure* FetchModelStructure(const char* path);
        mjModelStructure* FetchModelStructure(std::string& path);

        mjSoundResource* FetchSound(const char* path);
        mjSoundResource* FetchSound(std::string& path);

        mjShaderResource* FetchShader(const char* name);
        mjShaderResource* FetchShader(std::string& name);
        mjShaderResource* PushShader(std::string& name, std::string& vertexShader, std::string& fragmentShader);
        mjShaderResource* PushShader(mjShader* shader);

        mjGraphicCharObjectResource* FetchGraphicChar(mjFontResource* fontResource, int fontSize,
                                                      unsigned long charToRenderLong);

        mjFontResource* FetchFont(std::string& path);

        void PrependFullFilePath(std::string& filePath);

        //! Always, ALWAYS write directory separators as "/". Then use this function to properly access things in Windows.
        void ReplaceDirectorySeparators(std::string& filePath);



        //! Note: DO ___NOT___ try to free this buffer yourself. The system does it for you
        mjFileFromArchive* ReadAllFromArchiveToBuffer(const char* filename, const unsigned char** buffer, size_t* readSize);

        mjFileFromArchive* OpenFromArchive(const char* path, ArchiveReadMode readMode = READ_MODE_NO_ASSUMPTIONS);
        static size_t ReadFromArchive(mjFileFromArchive* mjFile, const unsigned char* buffer, size_t howMany);
        void CloseAndFreeResources(mjFileFromArchive** mjFile);



protected:
        std::vector<mjResource*> models;
        std::vector<mjResource*> textures;
        std::vector<mjResource*> modelStructures;
        std::vector<mjResource*> soundResources;
        std::vector<mjResource*> shaderResources;
        std::vector<mjResource*> fontResources;

        std::vector<mjResource*> graphicCharObjectResources;


        std::string pathPrefix;
        mjRenderer* renderer = NULL;

        int soundIndexAndroid = 0;

        char separator;

        mjResource* SearchByPath(std::vector<mjResource*>& repo, std::string& path, int modifier=0);
        mjResource* SearchByPathIgnoreExtension(std::vector<mjResource*>& repo, std::string& path, int modifier=0);

        mjResource* SearchByIdentifier(std::vector<mjResource* > &repo, unsigned long identifier, int modifier);



    private:
        FT_Library ft;

#ifdef ANDROID_ASSMAN
        AAsset* ass = NULL;
#endif

};

}

#endif // MJRESOURCEMANAGER_H
