#include "BatBot.h"

// Putting the BatMaton header files here makes it possible to use the BatMaton states without having definition problems.
// Both classes have been defined by now, so they can be used directly

#include "batMatonStates/WanderBatMatonState.h"

BatBot::BatBot(Level* levelData, mjResourceManager& resourceManager):
mjObject(MJ_AABB)
//:BatMaton(levelData)
{
    this->levelData = levelData;

    wanderDir.Set(-1,0,0);
    anchor.Set(2.34, 7.9, -7.42);

    BatAutomatonState* wander = new WanderBatMatonState(this);
    states.push_back(wander);

    Start(wander);



	GLuint glTexture;

	model = resourceManager.FetchModel("bird.mesh.xml");
	((mjAABB*)boundingStructure)->isImmovable = true;

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
}


BatBot::BatAutomatonState::BatAutomatonState(BatBot* bat)
{
    this->bat = bat;
}


void BatBot::Update(float t_elapsed)
{
	if (t_elapsed < 1)
	{
		mjAutomaton::Update(t_elapsed);
		mjObject::UpdatePosition(t_elapsed);

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

		vel.ScaleAdd(t_elapsed, accel);

	}
}
