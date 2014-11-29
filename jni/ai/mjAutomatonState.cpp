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

void mjAutomatonState::Enter()
{

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
void mjAutomatonState::SwitchToState(int destState)
{
    switchToStateNow = destState;
}

void mjAutomatonState::Leave()
{
    Reset();
}

}
