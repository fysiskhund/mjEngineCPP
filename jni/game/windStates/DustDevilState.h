#ifndef DUSTDEVILSTATE_H
#define DUSTDEVILSTATE_H

#include "WindState.h"

using namespace mjEngine;

class DustDevilState : public WindState
{
    public:
        float theta;
        int hDirection;
        float intensity;

        DustDevilState(mjVector3* wind);
        void Enter() override;
        void Execute(double t_elapsed) override;
    protected:
    private:
};

#endif // DUSTDEVILSTATE_H
