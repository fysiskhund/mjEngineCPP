#include "FrogBoss.h"

#include "frogBossAutomatonStates/FrogBossAutomatonHuntState.h"
#include "frogBossAutomatonStates/FrogBossAutomatonSlamState.h"
#include "frogBossAutomatonStates/FrogBossAutomatonWaitForLandingState.h"

FrogBoss::FrogBoss(Level* levelData, mjResourceManager* resourceManager)
: KosmoObject(MJ_AABB, resourceManager, levelData)
{
    srand(time(0));


    model = resourceManager->FetchModel("evilfrog.mesh.xml");

    glTexture = resourceManager->FetchTexture("evilfrog.png", GL_REPEAT);//("/sdcard/mjEngineCPP/bluesky/wandering_cloud0.png"); //
	for (unsigned i = 0; i < model->meshes.size(); i++)
	{
		model->meshes[i]->glTexture = glTexture;
	}

    FrogBossAutomatonState* waitForLandingState = new FrogBossAutomatonWaitForLandingState(this);
    FrogBossAutomatonState* huntState = new FrogBossAutomatonHuntState(this);
    FrogBossAutomatonState* slamState = new FrogBossAutomatonSlamState(this);


    states.push_back(waitForLandingState);
    states.push_back(huntState);
    states.push_back(slamState);
    SetStartState(waitForLandingState);

    MatchAABBToModel();

    soundSource = new mjSoundSource();
    soundSource->attenuation = 0.001; // Essentially heard everywhere
    soundSource->Load(resourceManager->FetchSound("sounds/ribbit.wav"), 0);

    gravity.y = -9.81;
}

void FrogBoss::Update(float t_elapsed)
{
    if (target == NULL)
    {
        target = (KosmoObject*) levelData->GetEntityByID("character0");
    }

	mjAutomaton::Update(t_elapsed);
    KosmoObject::UpdatePosition(t_elapsed);

}

FrogBoss::FrogBossAutomatonState::FrogBossAutomatonState(FrogBoss* frogBoss)
{
    this->frogBoss = frogBoss;
}


void FrogBoss::SetDetailsFromXML(XMLElement* entity)
{
    KosmoObject::SetDetailsFromXML(entity);
    startPosition.CopyFrom(pos);
    mjAABB* mjaabbStruct = (mjAABB*) boundingStructure;
    mjaabbStruct->UpdateCorners();
}


void FrogBoss::ProcessCollisionEffects()
{

    int previousFootingValue = hasFooting;
    hasFooting = 0;

    for (unsigned i=0; i < collisionStack.size(); i++)
    {
        mjPhysicsEffect* collisionEffect = collisionStack[i];

        /*if (collisionEffect->value.Check(__FILE__, __LINE__))
        {
            LOGI("CEff: 0x%x, otherObj: 0x%x", collisionEffect, collisionEffect->otherObject);
        }*/
        //LOGI("collisionEffect.value: %3.3f %3.3f %3.3f", collisionEffect->value.x,collisionEffect->value.y, collisionEffect->value.z);

        switch(collisionEffect->action)
        {
        case MJ_CHANGE_POSITION:
        {

            mjVector3 maskDirection;

            maskDirection.Set(collisionEffect->mask[0], collisionEffect->mask[1], collisionEffect->mask[2]);


            maskDirection.Normalize();

            mjVector3 gravityNormalized;
            gravityNormalized.CopyFrom(gravity);
            gravityNormalized.Normalize();
            if (gravityNormalized.Dot(maskDirection) < -0.4)
            {
                if (!previousFootingValue)
                {
                    //LOGI("char: hasFooting -> yes");



                }
                hasFooting = 1;
                //objectProvidingFooting = collisionEffect->otherObject;
            } else {
                //LOGI("noFooting");
            }

        }
            break;
        case MJ_ADD_VELOCITY:
            if(LAME_FIX_alreadyProcessedSpeedForThisFrame || collisionEffect->otherObject == target)
            {
                collisionEffect->value.Set0();
            } else
            {
                LAME_FIX_alreadyProcessedSpeedForThisFrame = true;
            }
            break;
        default:
            //whatever
            break;
        }
    }

    if (previousFootingValue && (hasFooting == 0))
    {
        //LOGI("char: hasFooting -> *no*");
    }


    KosmoObject::ProcessCollisionEffects();
    LAME_FIX_alreadyProcessedSpeedForThisFrame = false;

}
void FrogBoss::ResetByDefeat()
{
    wasDefeated = true;

    Reset();
}
void FrogBoss::Reset()
{
    pos.CopyFrom(startPosition);
    vel.Set0();
}

