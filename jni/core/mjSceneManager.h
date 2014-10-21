#ifndef MJSCENEMANAGER_H
#define MJSCENEMANAGER_H

#include <vector>
#include "mjScene.h"


namespace mjEngine{



class mjSceneManager
{
    public:
        std::vector<mjScene*> scenes;

        mjSceneManager();
    protected:
    private:
};

}
#endif // MJSCENEMANAGER_H
