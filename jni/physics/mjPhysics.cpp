
#include "mjPhysics.h"

namespace mjEngine
{

mjPhysics::mjPhysics()
{

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
		if (allObjects[i].hasKinematics)
		{
			//allObjects[i].effectStack.add(gravityEffect);
		}
		allObjects[i].ProcessPhysicsEffects();
		allObjects[i].Update(t_elapsed);
	}
}
}
