#include "Ambient.h"

Ambient::Ambient()
{
    windAutomaton.states.push_back(new SteadyDirectionState(&wind));
    windAutomaton.Start(windAutomaton.states[0]);


    for (unsigned i = 0; i < windAutomaton.states.size(); i++)
    {
       ((WindState*) windAutomaton.states[i])->stateCount = windAutomaton.states.size();
    }
}

void Ambient::Update(float t_elapsed)
{
    windAutomaton.Update(t_elapsed);

}
