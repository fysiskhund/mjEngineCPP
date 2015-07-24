#include "mjAutomaton.h"
namespace mjEngine {

mjAutomaton::mjAutomaton()
{
    //ctor
}

void mjAutomaton::SetStartState(mjAutomatonState* initialState)
{
currentState = initialState;
currentState->Enter();
}

mjAutomaton::~mjAutomaton()
{
    //dtor..
}

void mjAutomaton::Update(float t_elapsed)
{
    if (currentState)
    {
        currentState->Execute(t_elapsed);
        currentState->Update(t_elapsed);

        int destState = -1;
        if (currentState->switchToStateNow > -1)
        {
            destState = currentState->switchToStateNow;
        } else if ((currentState->maxTime > 0) && (currentState->accumulatedTime > currentState->maxTime) && (currentState->destStateOnTimeExpiration > -1))
        {
            destState = currentState->destStateOnTimeExpiration;
        }
        if (destState > -1)
        {
            currentState->Leave();
            currentState->switchToStateNow = -1;
            currentState = states[destState];
            currentState->Enter();
        }
    }
}

mjAutomaton::mjAutomaton(const mjAutomaton& other)
{
    //copy ctor
}

}
