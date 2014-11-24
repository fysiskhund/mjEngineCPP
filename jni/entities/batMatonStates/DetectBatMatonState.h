#ifndef DETECTBATMATONSTATE_H
#define DETECTBATMATONSTATE_H

#include "../BatBot.h"

class DetectBatMatonState
{
    public:
        DetectBatMatonState(BatBot* bat);
        mjObject* player;
        virtual ~DetectBatMatonState();
    protected:
    private:
};

#endif // DETECTBATMATONSTATE_H
