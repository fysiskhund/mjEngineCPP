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
        virtual void Update(float t_elapsed);

        mjAutomatonState* currentState;
        std::vector<mjAutomatonState*> states;
    protected:
    private:
};

}
#endif // MJAUTOMATON_H
