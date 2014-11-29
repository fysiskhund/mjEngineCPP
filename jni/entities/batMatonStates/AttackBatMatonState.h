#ifndef ATTACKBATMATONSTATE_H
#define ATTACKBATMATONSTATE_H

#include "../BatBot.h"

class AttackBatMatonState: public BatBot::BatAutomatonState
{
    public:
        AttackBatMatonState(BatBot* bat);
        //virtual void Execute(float t_elapsed) override;
        //virtual void Reset() override;
        virtual ~AttackBatMatonState();
        mjObject* player = NULL;
    protected:
    private:
};

#endif // ATTACKBATMATONSTATE_H
