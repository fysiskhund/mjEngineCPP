
#include "mjPhysics.h"

namespace mjEngine
{

mjPhysics::mjPhysics()
{

}

void mjPhysics::AddObject(mjObject* object, int collisionLayer)
{
	allObjects.push_back(object);

	if (object->hasKinematics)
	{
		objectsWithKinematics.push_back(object);
	}
	if (object->canCollide)
	{
		while (collisionLayers.size() <= (collisionLayer + 1))
		{
			collisionLayers.push_back(new std::vector<mjObject* >());
		}
		collisionLayers[collisionLayer]->push_back(object);

	}
}

void mjPhysics::Update(float t_elapsed)
{

	CollisionDetection();

	ProcessPhysicsEffects(t_elapsed);

}


void mjPhysics::CollisionDetection()
{

}
void mjPhysics::ProcessPhysicsEffects(float t_elapsed)
{
	for(int i = 0; i < allObjects.size(); i++)
	{
		if (allObjects[i]->hasKinematics)
		{
			//allObjects[i].effectStack.add(gravityEffect);
		}
		allObjects[i]->ProcessPhysicsEffects();
		allObjects[i]->Update(t_elapsed);
	}
}
}
