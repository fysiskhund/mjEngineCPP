#ifndef FROGJUMPAUTOMATONSTATE_H
#define FROGJUMPAUTOMATONSTATE_H

#include <physics/mjCollisionTests.h>

#include "../Frog.h"


class FrogAutomatonJumpState: public Frog::FrogAutomatonState
{
    public:
        FrogAutomatonJumpState(Frog* frog);
        void Enter() override;
        void Execute(float t_elapsed) override;
    protected:
    private:
};

#endif // FROGJUMPAUTOMATONSTATE_H
