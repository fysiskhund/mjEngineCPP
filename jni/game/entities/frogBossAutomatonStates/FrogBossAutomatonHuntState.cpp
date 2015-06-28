#include "FrogBossAutomatonHuntState.h"

FrogBossAutomatonHuntState::FrogBossAutomatonHuntState(FrogBoss* frogBoss):
FrogBoss::FrogBossAutomatonState::FrogBossAutomatonState(frogBoss)
{

    destStateOnTimeExpiration = 2;

}

void FrogBossAutomatonHuntState::Enter()
{

    LOGI("FrogBaws: Searching for Kosmonavt..");

    frogBoss->vel.Set0();

    if (frogBoss->wasDefeated)
    {
        frogBoss->defeatedTimes++;
        frogBoss->berserkTimes = frogBoss->defeatedTimes*3.5;
        frogBoss->wasDefeated = false;
    }

    if (frogBoss->berserkTimes > 0)
    {
        LOGI("FrogBaws: defeated %d times; BERSERK!!!!! [%d]", frogBoss->defeatedTimes, frogBoss->berserkTimes)
        maxTime = ((float)rand() / (float) RAND_MAX) + 0.001;
        frogBoss->berserkTimes--;
    } else
    {
        maxTime = 2.0*((float)rand() / (float) RAND_MAX) + 2.0;
    }

}


void FrogBossAutomatonHuntState::Execute(float t_elapsed)
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
        // FrogBaws has acquired target and should always look at it
        mjVector3 dirToTarget(frogBoss->pos, frogBoss->target->pos);

        dirToTarget.y = 0; // remove vertical component

        if (dirToTarget.GetNormSquared() < 0.001)
        {
            dirToTarget.Set(0,0,-1);
        } else
        {
            dirToTarget.Normalize();
        }
        frogBoss->dir.CopyFrom(dirToTarget);

    }

}

void FrogBossAutomatonHuntState::Leave()
{

    FrogBossAutomatonState::Leave();
}
