#ifndef FROG_H
#define FROG_H


#include <vector>

#include "../core/mjObject.h"
#include "../game/Level.h"
#include "../ai/mjAutomaton.h"
#include "../extLibs/util/mjXMLHelper.h"

class Frog : public mjObject
{
    public:
        Frog(Level* levelData, mjResourceManager& resourceManager);
        Level* levelData;
        unsigned glTexture;

class FrogAutomatonState: public mjAutomatonState
        {
        public:
            FrogAutomatonState(Frog* frog);
            Frog* frog;
        };

    protected:
    private:
};



#endif // FROG_H
