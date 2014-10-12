#include "BatBot.h"

BatBot::BatBot(Level* levelData)
:BatMaton(levelData)
{
    this->levelData = levelData;
}


/*BatBot::BatBot(const BatBot& other)
{
    //copy ctor
}*/
