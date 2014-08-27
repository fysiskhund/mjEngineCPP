
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
	// Objects in layer 0 are tested against other objects in layer 0

	if (collisionLayers.size() > 0)
	{

		for (int i = 0; i < collisionLayers[0]->size(); i++)
		{
			mjObject* objectI = (*collisionLayers[0])[i];
			for (int j = i+1; j < collisionLayers[0]->size(); j++)
			{
				mjObject* objectJ = (*collisionLayers[0])[j];
				mjObject* object0;
				mjObject* object1;
				if (objectI->boundingStructure->type < objectJ->boundingStructure->type)
				{
					object0 = objectI;
					object1 = objectJ;
				} else
				{
					object0 = objectJ;
					object1 = objectI;
				}

				switch(object0->boundingStructure->type)
				{
				case MJ_SPHERE:
				{
					switch(object1->boundingStructure->type){
					case MJ_SPHERE:
					{
						mjCollisionResult* colResult = new mjCollisionResult();
						if (mjCollisionTests::SphereVsSphere(*(mjSphere*) object0, *(mjSphere*) object1, colResult) == MJ_OVERLAP)
						{
							LOGI("Collision!\n");
						} else
						{
							LOGI("No collision!\n");
						}
					}
						break;
					default:
						break;
					}
				}
					break;
				default:
					break;
				}
			}
		}
	}
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
