#include "FrogBossAutomatonWaitForLandingState.h"

FrogBossAutomatonWaitForLandingState::FrogBossAutomatonWaitForLandingState(FrogBoss* frogBoss):
FrogBoss::FrogBossAutomatonState::FrogBossAutomatonState(frogBoss)
{

    destStateOnTimeExpiration = 1;
}

void FrogBossAutomatonWaitForLandingState::Enter()
{
    maxTime = -1;
    LOGI("FrogBaws: Waiting for landing..");


}


void FrogBossAutomatonWaitForLandingState::Execute(float t_elapsed)
{
    // if frog falls
    if (mjCollisionTests::AABBVsAABB((mjAABB*) frogBoss->boundingStructure, frogBoss->levelData->hardLimits, NULL) != MJ_OVERLAP)
    {
        if (frogBoss->pos.y < frogBoss->levelData->hardLimits->center->y+frogBoss->levelData->hardLimits->halfWidths.y)
        {
            frogBoss->ResetByDefeat();
        }
    } else
    {

       mjVector3 posToTarget(frogBoss->pos, frogBoss->target->pos);
       float distToTargetSquared = posToTarget.GetNormSquared();
       if (frogBoss->hasFooting && distToTargetSquared < 900) // 30 m -> 30*30 -> 900
       {
           if (frogBoss->firstTimeTargetSeen)
           {
               frogBoss->wasDefeated = false;
               frogBoss->defeatedTimes = 0;
               frogBoss->berserkTimes = 0;
               frogBoss->firstTimeTargetSeen = false;
               accumulatedTime = 0;
               maxTime = 8;
               LOGI("FrogBaws: First time target is seen.");
               maxTimeMustBeReset = false;
           } else
           {

               if (maxTimeMustBeReset)
               {

                   if (frogBoss->berserkTimes == 0)
                   {
                       maxTime = 0.5;
                   } else
                   {
                       maxTime = 0.1;
                   }
                   maxTimeMustBeReset = false;
               }
           }
       }
    }

}

void FrogBossAutomatonWaitForLandingState::Leave()
{
    maxTimeMustBeReset = true;
    FrogBossAutomatonState::Leave();
}
