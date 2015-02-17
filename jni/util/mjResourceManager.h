#ifndef MJRESOURCEMANAGER_H
#define MJRESOURCEMANAGER_H

#include <string>
#include <vector>

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

        GLuint FetchTexture(const char* path);
        GLuint FetchTexture(std::string& path);

        mjModelStructure* FetchModelStructure(const char* path);
        mjModelStructure* FetchModelStructure(std::string& path);

        mjSoundResource* FetchSound(const char* path);
        mjSoundResource* FetchSound(std::string& path);
    protected:
        std::vector<mjResource*> models;
        std::vector<mjResource*> textures;
        std::vector<mjResource*> modelStructures;
        std::vector<mjResource*> soundResources;

        std::string pathPrefix;

        int soundIndexAndroid = 0;

        mjResource* SearchByPath(std::vector<mjResource*>& repo, std::string& path);

    private:
};

}

#endif // MJRESOURCEMANAGER_H
