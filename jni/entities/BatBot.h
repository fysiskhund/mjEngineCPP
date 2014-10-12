#ifndef BATBOT_H
#define BATBOT_H

#include "../core/mjObject.h"
#include "../game/Level.h"
#include "BatMaton.h"


using namespace mjEngine;

class BatBot: public mjObject, public BatMaton
{
    public:
        BatBot(Level* levelData);
        //BatBot(const BatBot& other);
        Level* levelData;
    protected:
    private:
};

#endif // BATBOT_H
