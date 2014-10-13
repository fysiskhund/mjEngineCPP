#include "BatAutomatonCreator.h"

BatAutomatonCreator::BatAutomatonCreator(BatBot* bat)
{
    BatBot::BatAutomatonState* wander = new WanderBatMatonState(bat);

}
