#include "mjAutomaton.h"
namespace mjEngine {

mjAutomaton::mjAutomaton()
{
    //ctor
}

void mjAutomaton::Start(mjAutomatonState* initialState)
{
currentState = initialState;
currentState->Enter();
}

mjAutomaton::~mjAutomaton()
{
    //dtor
}

void mjAutomaton::Update(float t_elapsed)
{
    if (currentState)
    {
        currentState->Execute(t_elapsed);
        currentState->Update(t_elapsed);
        if (currentState->maxTime > 0 && (currentState->accumulatedTime > currentState->maxTime))
        {
            if (currentState->destStateOnTimeExpiration > -1)
            {
                currentState->Leave();
                int destStateOnTimeExpiration = currentState->destStateOnTimeExpiration;
                currentState = states[destStateOnTimeExpiration];
                currentState->Enter();
            }
        }

    }
}

mjAutomaton::mjAutomaton(const mjAutomaton& other)
{
    //copy ctor
}

}
