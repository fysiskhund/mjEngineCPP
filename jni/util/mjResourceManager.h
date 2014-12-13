#ifndef MJRESOURCEMANAGER_H
#define MJRESOURCEMANAGER_H

#include <string>
#include <vector>

#include "../graphics/mjModel.h"
#include "../graphics/mjImageLoader.h"
#include "mjModelResource.h"
#include "mjTextureResource.h"

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

        mjModelPose* FetchPose(const char* path);
        mjModelPose* FetchPose(std::string& path);
    protected:
        std::vector<mjResource*> models;
        std::vector<mjResource*> textures;
        std::vector<mjResource*> poses;

        std::string pathPrefix;

        mjResource* SearchByPath(std::vector<mjResource*>& repo, std::string& path);

    private:
};

}

#endif // MJRESOURCEMANAGER_H
