#ifndef DETECTBATMATONSTATE_H
#define DETECTBATMATONSTATE_H

#include "../BatBot.h"

#define DETECT_DISTANCE 4.0

class DetectBatMatonState: public BatBot::BatAutomatonState
{
    public:
        DetectBatMatonState(BatBot* bat);
        mjObject* player;
        virtual void Execute(float t_elapsed) override;
        virtual void Reset() override;
        virtual ~DetectBatMatonState();
    protected:
    private:
};

#endif // DETECTBATMATONSTATE_H
