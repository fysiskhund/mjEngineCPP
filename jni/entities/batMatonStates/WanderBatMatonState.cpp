#include "WanderBatMatonState.h"

WanderBatMatonState::WanderBatMatonState(BatBot* bat)
:BatBot::BatAutomatonState::BatAutomatonState(bat)
{
    bobVector.Set(0,1,0);
	player = bat->levelData->GetEntityByID("character0");

}

void WanderBatMatonState::Execute(float t_elapsed)
{

    mjVector3 dirToAnchor;


    dirToAnchor.CopyFrom(bat->anchor);
    dirToAnchor.Subtract(bat->pos);
    float dist = dirToAnchor.Normalize();

    if (dist > bat->wanderRadiusMax)
    {
        bat->wanderDir.CopyFrom(dirToAnchor);
        twistDirFactor *= -1;
    } else if (dist < bat->wanderRadiusMin)
    {
        bat->wanderDir.CopyFrom(dirToAnchor);
        bat->wanderDir.MulScalar(-1);
    }

    mjVector3 twistVector;

    bat->wanderDir.CrossOut(bat->up, &twistVector);
    twistVector.Normalize();

    bat->wanderDir.ScaleAdd(0.013, twistVector);

    if (bobVector.y > 0)
    {
    	goingUpTime -= t_elapsed;
    	bat->wanderDir.ScaleAdd(0.6, bobVector);
    	if (goingUpTime < 0)
    	{
    		goingDownTime = TOTAL_FLOP_TIME;
    		bobVector.y = -1;
    	}
    } else
    {
    	goingDownTime -= t_elapsed;
    	bat->wanderDir.ScaleAdd(0.15, bobVector);
    	if (goingDownTime < 0)
    	{
    		goingUpTime = TOTAL_FLOP_TIME*0.25;
    		bobVector.y = 1;
    	}
    }



    bat->wanderDir.Normalize();


    bat->pos.ScaleAdd(t_elapsed*3.0, bat->wanderDir);

    bat->wanderDir.y = 0;
    bat->dir.CopyFrom(bat->wanderDir);
    bat->dir.Normalize();

    //LOGI("wanderDir: %3.3f, %3.3f, %3.3f", bat->wanderDir.x, bat->wanderDir.y, bat->wanderDir.z);
    //LOGI("batPos: %3.3f, %3.3f, %3.3f", bat->pos.x, bat->pos.y, bat->pos.z);
	if (player)
	{

	}
}