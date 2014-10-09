#include "mjAutomatonState.h"

namespace mjEngine {

mjAutomatonState::mjAutomatonState()
{
    //ctor
}

mjAutomatonState::~mjAutomatonState()
{
    //dtor
}

void mjAutomatonState::Execute(float t_elapsed)
{
}
void mjAutomatonState::Update(float t_elapsed)
{
    if (maxTime > 0)
    {
        accumulatedTime += t_elapsed;
    }
}

void mjAutomatonState::Reset()
{
    accumulatedTime = 0;
}

}