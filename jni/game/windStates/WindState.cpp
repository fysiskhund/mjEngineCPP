#include "WindState.h"



WindState::WindState(mjVector3* wind)
{
    srand(time(NULL));
    this->wind = wind;
}
void WindState::Enter()
{
    maxTime = 4.0 + ((float)rand()/(float)RAND_MAX)*15.0;
    destStateOnTimeExpiration = ((float)rand()/(float)RAND_MAX)*stateCount;
}

void WindState::Leave()
{
    Reset();

}






