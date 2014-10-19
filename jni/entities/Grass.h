#ifndef GRASS_H
#define GRASS_H

#include "../core/mjObject.h"
#include "../ai/mjAutomaton.h"

#include "../game/Level.h"

using namespace mjEngine;

class Grass : public mjObject, public mjAutomaton
{
    public:
        Grass(Level* levelData);
        //BatBot(const BatBot& other);
        Level* levelData;
        ~Grass();
        virtual void ProcessPhysicsEffects(float t_elapsed) override;
    protected:
    private:
};

#endif // GRASS_H
