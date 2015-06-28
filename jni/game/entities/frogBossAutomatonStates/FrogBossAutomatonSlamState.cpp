#include "FrogBossAutomatonSlamState.h"

FrogBossAutomatonSlamState::FrogBossAutomatonSlamState(FrogBoss* frogBoss):
FrogBoss::FrogBossAutomatonState::FrogBossAutomatonState(frogBoss)
{
    destStateOnTimeExpiration = 0;

}

void FrogBossAutomatonSlamState::Enter()
{
    LOGI("FrogBaws: SLAMMIN'!");

    frogBoss->soundSource->Play(frogBoss->pos, 0);

    maxTime = 2; // Slam 'flight' takes 2 seconds

    // let's get slammin'
    frogBoss->slamLocation.CopyFrom(frogBoss->target->pos);

    frogBoss->launchLocation.CopyFrom(frogBoss->pos);

    trajectory.CopyFrom(frogBoss->slamLocation);
    trajectory.Subtract(frogBoss->launchLocation);



    if (frogBoss->slamLocation.y > frogBoss->launchLocation.y)
    {
        trajectory.y = frogBoss->slamLocation.y + 5;
    } else
    {
        trajectory.y = frogBoss->launchLocation.y + 5;
    }


}

void FrogBossAutomatonSlamState::Execute(float t_elapsed)
{
    if (mjCollisionTests::AABBVsAABB((mjAABB*)frogBoss->boundingStructure, frogBoss->levelData->hardLimits, NULL) == MJ_NO_COLLISION)
    {
        // The frogBoss is immune to the upper limit in the level.
        // but in other cases, it will die
        if (frogBoss->pos.y < frogBoss->levelData->hardLimits->center->y+frogBoss->levelData->hardLimits->halfWidths.y)
        {
            frogBoss->ResetByDefeat();
        }
    } else
    {
        if (accumulatedTime < maxTime/2.0)
        {
            frogBoss->vel.y += 0.7;

        } else
        {
            if (frogBoss->vel.y > 0)
            {
                frogBoss->vel.y = 0;
            }
            frogBoss->vel.y -= 0.2;
        }
        float newX = frogBoss->launchLocation.x + ((accumulatedTime/maxTime)*trajectory.x);
        float newZ = frogBoss->launchLocation.z + ((accumulatedTime/maxTime)*trajectory.z);

        frogBoss->pos.x = newX;
        frogBoss->pos.z = newZ;
    }


}
