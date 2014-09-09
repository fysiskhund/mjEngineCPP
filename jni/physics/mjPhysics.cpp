
#include "mjPhysics.h"

namespace mjEngine
{

mjPhysics::mjPhysics()
{
	gravity.Set(0,-9.81,0);
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
				//LOGI("phys: i:%d, j:%d\n", i, j);
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
						//LOGI("sphVsph");
						mjCollisionResult* colResult = new mjCollisionResult();
						//LOGI("After new Colresult");
						if (mjCollisionTests::SphereVsSphere((mjSphere*)object0->boundingStructure, (mjSphere*)object1->boundingStructure, colResult) == MJ_OVERLAP)
						{
							colResult->relocationEffectObj0->otherObject = object1;
							object0->collisionStack.push_back(colResult->relocationEffectObj0);

							colResult->relocationEffectObj1->otherObject = object0;
							object1->collisionStack.push_back(colResult->relocationEffectObj1);
							//FIXME:!!! Something must be done with colResult in this case
							// without altering the inner effects, since those will be destroyed in the object after they'be been used.

						} else
						{
							delete colResult;
							//LOGI("No collision!\n");
						}
					}
						break;
					default:
						break;
					}
				}
					break;
				case MJ_AABB:
				{
					switch(object1->boundingStructure->type)
					{
					case MJ_AABB:
					{
						mjCollisionResult* colResult = new mjCollisionResult();

						if (mjCollisionTests::AABBVsAABB((mjAABB*)object0->boundingStructure, (mjAABB*)object1->boundingStructure, colResult) == MJ_OVERLAP)
						{

							if (object1->boundingStructure->isImmovable)
							{
								if (colResult->changeVelEffectObj0->mask[0])
								{
									colResult->changeVelEffectObj0->value.x *= fabs(object0->vel.x);
								}
								if (colResult->changeVelEffectObj0->mask[1])
								{
									colResult->changeVelEffectObj0->value.y *= fabs(object0->vel.y);
								}
								if (colResult->changeVelEffectObj0->mask[2])
								{
									colResult->changeVelEffectObj0->value.z *= fabs(object0->vel.z);
								}

							} else if (object0->boundingStructure->isImmovable)
							{
								if (colResult->changeVelEffectObj1->mask[0])
								{
									colResult->changeVelEffectObj1->value.x *= fabs(object1->vel.x);
								}
								if (colResult->changeVelEffectObj1->mask[1])
								{
									colResult->changeVelEffectObj1->value.y *= fabs(object1->vel.y);
								}
								if (colResult->changeVelEffectObj1->mask[2])
								{
									colResult->changeVelEffectObj1->value.z *= fabs(object1->vel.z);
								}

							}

							colResult->relocationEffectObj0->otherObject = object1;
							object0->collisionStack.push_back(colResult->relocationEffectObj0);
							object0->collisionStack.push_back(colResult->changeVelEffectObj0);

							colResult->relocationEffectObj1->otherObject = object0;
							object1->collisionStack.push_back(colResult->relocationEffectObj1);
							object1->collisionStack.push_back(colResult->changeVelEffectObj1);
							//FIXME:!!! Something must be done with colResult in this case
							// without altering the inner effects, since those will be destroyed in the object after they'be been used.

						}else
						{
							delete colResult;
							//LOGI("No collision!\n");
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
			mjPhysicsEffect* gravityEffect = new mjPhysicsEffect(MJ_GRAVITY, MJ_ADD_ACCEL);
			gravityEffect->value.Set(0,-9.81,0);
			allObjects[i]->effectStack.push_back(gravityEffect);
		}
		allObjects[i]->ProcessPhysicsEffects();
		allObjects[i]->Update(t_elapsed);
	}
}
}
