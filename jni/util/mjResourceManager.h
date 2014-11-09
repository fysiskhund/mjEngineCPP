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
        mjResourceManager();
        ~mjResourceManager();

        mjModel* FetchModel(const char* path);
        mjModel* FetchModel(std::string& path);

        GLuint FetchTexture(const char* path);
        GLuint FetchTexture(std::string& path);
    protected:
        std::vector<mjResource*> models;
        std::vector<mjResource*> textures;

        mjResource* SearchByPath(std::vector<mjResource*>& repo, std::string& path);
    private:
};

}

#endif // MJRESOURCEMANAGER_H
