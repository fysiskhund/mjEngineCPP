#include "BatBot.h"

// Putting the BatMaton header files here makes it possible to use the BatMaton states without having definition problems.
// Both classes have been defined by now, so they can be used directly

#include "batMatonStates/WanderBatMatonState.h"
#include "batMatonStates/DetectBatMatonState.h"
#include "batMatonStates/AttackBatMatonState.h"

BatBot::BatBot(Level* levelData, mjResourceManager& resourceManager):
mjObject(MJ_AABB)
//:BatMaton(levelData)
{

    //Animation test
    mjAnimationSegment* segment0 = new mjAnimationSegment();
    segment0->meshNum = 0;
    segment0->totalTime = 0.8;

    mjAnimationKeyframe* keyframe0 = new mjAnimationKeyframe();

    keyframe0->angles.y = M_PI_4;
    keyframe0->timeStamp = 0;

    mjAnimationKeyframe* keyframe1 = new mjAnimationKeyframe();

    keyframe1->angles.y = -M_PI_4;
    keyframe1->timeStamp = 0.4;

    mjAnimationKeyframe* keyframe2 = new mjAnimationKeyframe();

    keyframe2->angles.y = M_PI_4;
    keyframe2->timeStamp = 0.8;



    segment0->keyframes.push_back(keyframe0);
    segment0->keyframes.push_back(keyframe1);
    segment0->keyframes.push_back(keyframe2);

    animation.segments.push_back(segment0);

    pose = new mjModelPose();
    pose->angles.push_back(new mjVector3());
    pose->positions.push_back(new mjVector3());


//////////// end of animation test (init)


    this->levelData = levelData;

    wanderDir.Set(-1,0,0);
   // anchor.Set(2.34, 7.9, -7.42);

    BatAutomatonState* wander = new WanderBatMatonState(this);
    BatAutomatonState* detect = new DetectBatMatonState(this);
    BatAutomatonState* attack = new AttackBatMatonState(this);
    states.push_back(wander);
    states.push_back(detect);
    states.push_back(attack);

    SetStartState(wander);



	GLuint glTexture;

	model = resourceManager.FetchModel("bird.mesh.xml");
	((mjAABB*)boundingStructure)->isImmovable = false;

	glTexture = resourceManager.FetchTexture("birdtexture.png");//("/sdcard/mjEngineCPP/bluesky/wandering_cloud0.png"); //
	for (unsigned i = 0; i < model->meshes.size(); i++)
	{
		model->meshes[i]->glTexture = glTexture;
	}
}

void BatBot::SetDetailsFromXML(XMLElement* entity)
{
    mjObject::SetDetailsFromXML(entity);

    anchor.CopyFrom(pos);
    pos.x += 1; // Avoid pos === anchor, which causes problems.
    LOGI("batbot: pos set to %3.3f %3.3f %3.3f", pos.x, pos.y , pos.z);
    LOGI("vInit: %3.3f, %3.3f, %3.3f", this->vel.x, this->vel.y, this->vel.z);
}


BatBot::BatAutomatonState::BatAutomatonState(BatBot* bat)
{
    this->bat = bat;
}


void BatBot::Update(float t_elapsed)
{
	if (t_elapsed < 1)
	{
        tAnimation += t_elapsed;

        if (tAnimation > 0.8)
            tAnimation -= 0.8;

        animator.UpdatePose(tAnimation, *pose, animation);

		mjAutomaton::Update(t_elapsed);
		mjObject::UpdatePosition(t_elapsed);
		LOGI("Batbot: I exist at %3.3f %3.3f %3.3f with anchor %3.3f, %3.3f, %3.3f", this->pos.x, this->pos.y, this->pos.z, this->anchor.x, this->anchor.y, this->anchor.z);
		LOGI("v: %3.3f, %3.3f, %3.3f", this->vel.x, this->vel.y, this->vel.z);

	} else
	{
		LOGI("Bat->Update *cough*");
	}
}


void BatBot::ProcessPhysicsEffects(float t_elapsed)
{
	accel.Set0();

	for (unsigned i = 0; i < effectStack.size(); i++)
	{
		switch(effectStack[i]->type)
		{
			case MJ_ACCELERATION:
                accel.Add(effectStack[i]->value);
                break;
			case MJ_GRAVITY:
				if (!ignoresGravity)
				{
                    accel.Add(effectStack[i]->value);
				}

			break;
			default:
				break;
		}

		//if (effectStack[i]->)
	}
	effectStack.clear();


	if (!boundingStructure->isImmovable)
	{
		if (accel.GetNormSquared() < 100)
		{
			vel.ScaleAdd(t_elapsed, accel);
		} else
		{
			LOGI("Bat %s: accelAdd: %3.3f %3.3f %3.3f", id, accel.x, accel.y, accel.z);
		}


	}
}
