#ifndef BATMATON_H
#define BATMATON_H

#include "../ai/mjAutomaton.h"
#include "../game/Level.h"

using namespace mjEngine;

class BatMaton : public mjAutomaton
{
    public:
        BatMaton(Level* levelData);
        Level* levelData;

    protected:
    private:
};

#endif // BATMATON_H
