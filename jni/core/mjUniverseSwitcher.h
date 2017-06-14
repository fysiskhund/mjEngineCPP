#ifndef MJSCENEMANAGER_H
#define MJSCENEMANAGER_H

#include <vector>
#include "mjUniverse.h"
#include "mjTransitionUniverse.h"


namespace mjEngine{



class mjUniverseSwitcher
{
    public:
        std::vector<mjUniverse*> universes;
        mjUniverse* currentUniverse = NULL;
        mjGameState* currentGameState;

        mjUniverseSwitcher();
        void SetFirstUniverse(mjUniverse* firstUniverse, mjGameState* currentGameState);

        void Update(double t_elapsed);
    protected:
    private:
};

}
#endif // MJSCENEMANAGER_H
