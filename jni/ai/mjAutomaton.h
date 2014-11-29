#ifndef MJAUTOMATON_H
#define MJAUTOMATON_H

#include <vector>
#include "mjAutomatonState.h"

namespace mjEngine {


class mjAutomaton
{
    public:
        mjAutomaton();
        ~mjAutomaton();
        mjAutomaton(const mjAutomaton& other);

        void SetStartState(mjAutomatonState* initialState);

        virtual void Update(float t_elapsed);



        std::vector<mjAutomatonState*> states;
    protected:
    private:
        mjAutomatonState* currentState;
};

}
#endif // MJAUTOMATON_H
