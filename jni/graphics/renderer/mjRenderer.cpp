#include "mjRenderer.h"

namespace mjEngine
{

void mjRenderer::StartCountingStateSwitches()
{
    stateSwitchCount = 0;
}

void mjRenderer::StopCountingStateSwitches()
{
    LOGI("%d state switches counted.", stateSwitchCount);
}




}
