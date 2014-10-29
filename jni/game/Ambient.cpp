#include "Ambient.h"

Ambient::Ambient()
{
	LOGI("Wind is at %p\n", &wind);
    windAutomaton.states.push_back(new SteadyDirectionState(&wind));
    //windAutomaton.states.push_back(new DustDevilState(&wind));
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
