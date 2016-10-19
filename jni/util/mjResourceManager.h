#ifndef MJRESOURCEMANAGER_H
#define MJRESOURCEMANAGER_H

#include <string>
#include <vector>
#include <algorithm>

#include "../extLibs/tinyxml/tinyxml2.h"

#include "../graphics/mjModel.h"
#include "../graphics/mjImageLoader.h"
#include "../graphics/animation/mjModelStructure.h"
#include "mjModelResource.h"
#include "mjTextureResource.h"
#include "mjModelStructureResource.h"
#include "mjSoundResource.h"
#include "mjShaderResource.h"
#include "graphics/mjShader.h"
#include "graphics/mjDefaultShaders.h"
#include "graphics/mjSkyboxShaders.h"
#include "graphics/renderer/mjRenderer.h"
#include "../text/mjTextShaders.h"




namespace mjEngine{

class mjResourceManager
{
    public:
        mjResourceManager(std::string& pathPrefix, mjRenderer* renderer);
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
        mjShaderResource* PushShader(std::string& name, mjShader* shader);



        void PrependFullFilePath(std::string& filePath);


        std::vector<mjShader*> shaderList;

protected:
        std::vector<mjResource*> models;
        std::vector<mjResource*> textures;
        std::vector<mjResource*> modelStructures;
        std::vector<mjResource*> soundResources;
        std::vector<mjResource*> shaderResources;


        std::string pathPrefix;
        mjRenderer* renderer = NULL;

        int soundIndexAndroid = 0;

        mjResource* SearchByPath(std::vector<mjResource*>& repo, std::string& path, int modifier=0);
        mjResource* SearchByPathIgnoreExtension(std::vector<mjResource*>& repo, std::string& path, int modifier=0);


        char separator;

    private:
};

}

#endif // MJRESOURCEMANAGER_H
