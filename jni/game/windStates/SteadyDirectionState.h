#ifndef STEADYDIRECTIONSTATE_H
#define STEADYDIRECTIONSTATE_H

#include "WindState.h"
#include "../../extLibs/logger/mjLog.h"

using namespace mjEngine;

class SteadyDirectionState : public WindState
{
    public:
        SteadyDirectionState(mjVector3* wind);
        void Enter() override;
    protected:
    private:
};

#endif // STEADYDIRECTIONSTATE_H
