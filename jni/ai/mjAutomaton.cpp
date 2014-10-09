#include "mjAutomaton.h"
namespace mjEngine {

mjAutomaton::mjAutomaton()
{
    //ctor
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
                currentState->Reset();
                int destStateOnTimeExpiration = currentState->destStateOnTimeExpiration;
                currentState = states[destStateOnTimeExpiration];
            }
        }

    }
}

mjAutomaton::mjAutomaton(const mjAutomaton& other)
{
    //copy ctor
}

}
