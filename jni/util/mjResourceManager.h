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



namespace mjEngine{

class mjResourceManager
{
    public:
        mjResourceManager(std::string& pathPrefix);
        ~mjResourceManager();

        mjModel* FetchModel(const char* path);
        mjModel* FetchModel(std::string& path);

        GLuint FetchTexture(const char* path, unsigned glTextureWrapParameter);
        GLuint FetchTexture(std::string& path, unsigned glTextureWrapParameter);

        mjModelStructure* FetchModelStructure(const char* path);
        mjModelStructure* FetchModelStructure(std::string& path);

        mjSoundResource* FetchSound(const char* path);
        mjSoundResource* FetchSound(std::string& path);


        void PrependFullFilePath(std::string& filePath);




    protected:
        std::vector<mjResource*> models;
        std::vector<mjResource*> textures;
        std::vector<mjResource*> modelStructures;
        std::vector<mjResource*> soundResources;

        std::string pathPrefix;

        int soundIndexAndroid = 0;

        mjResource* SearchByPath(std::vector<mjResource*>& repo, std::string& path, int modifier=0);

        char separator;

    private:
};

}

#endif // MJRESOURCEMANAGER_H
