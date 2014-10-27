#include "SteadyDirectionState.h"

SteadyDirectionState::SteadyDirectionState(mjVector3* wind)
:WindState(wind)
{
}
void SteadyDirectionState::Enter()
{
    WindState::Enter();

    wind->Set(RANDOM_F-0.5, RANDOM_F-0.5, RANDOM_F-0.5);
    wind->Normalize();
    wind->MulScalar(0.02);
    LOGI("new wind direction %3.2f %3.2f %3.2f\n", wind->x, wind->y, wind->z);
}


