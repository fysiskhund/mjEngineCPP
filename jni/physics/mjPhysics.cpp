
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
	ProcessPhysicsEffectsAndUpdate(t_elapsed);

	CollisionDetection();

	ProcessCollisionEffects();

	UpdatePositions(t_elapsed);

}


void mjPhysics::CollisionDetection()
{
	// Objects in layer 0 are tested against other objects in layer 0

	int collisionLayerNum = collisionLayers.size();
	if (collisionLayerNum > 0)
	{


		// Only objects in collision layer 0 are tested against other objects in that same layer.
		// Objects in other layers are only tested against objects in other layers.
		for (int layerA = 0; layerA < collisionLayerNum; layerA++)
		{
			for (int layerB = 0; layerB < collisionLayerNum; layerB++ )
			{
				if (layerA != 0)
				{
					layerB = layerA+1;
					if (layerB >= collisionLayerNum)
					{
						break;
					}
				}
				int objectsInCollisionLayerANum = collisionLayers[layerA]->size();
				for (int i = 0; i < objectsInCollisionLayerANum; i++)
				{
					mjObject* objectI = (*collisionLayers[layerA])[i];

					int objectsInCollisionLayerBNum = collisionLayers[layerB]->size();

					for (int j = 0; j < objectsInCollisionLayerBNum; j++)
					{

						//LOGI("phys: i:%d, j:%d\n", i, j);
						mjObject* objectJ = (*collisionLayers[layerB])[j];
						if (objectI == objectJ)
						{
							j++;
							if (j >= objectsInCollisionLayerBNum)
							{
								break;
							}
							objectJ = (*collisionLayers[layerB])[j];
						}
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
#ifdef DEBUGCOLLISIONS
                        object0->DEBUGonCollisionTestStart(object1);
                        object1->DEBUGonCollisionTestStart(object0);
#endif

						mjCollisionResult* colResult = new mjCollisionResult(); // Prepare the collision result
						switch(object0->boundingStructure->type)
						{
						case MJ_SPHERE:
						{
							switch(object1->boundingStructure->type){
							case MJ_SPHERE:
							{
								//LOGI("sphVsph");

								//LOGI("After new Colresult");
								if (mjCollisionTests::SphereVsSphere((mjSphere*)object0->boundingStructure, (mjSphere*)object1->boundingStructure, colResult) == MJ_OVERLAP)
								{



									colResult->relocationEffectObj0->otherObject = object1;
									object0->collisionStack.push_back(colResult->relocationEffectObj0);

									colResult->relocationEffectObj1->otherObject = object0;
									object1->collisionStack.push_back(colResult->relocationEffectObj1);
									//FIXME:!!! Something must be done with colResult in this case
									// without altering the inner effects, since those will be destroyed in the object after they'be been used.
                                    object0->OnOverlap(object1);
                                    object1->OnOverlap(object0);


								} else
								{

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

								if (mjCollisionTests::AABBVsAABB((mjAABB*)object0->boundingStructure, (mjAABB*)object1->boundingStructure, colResult) == MJ_OVERLAP)
								{


									if (object1->boundingStructure->isImmovable)
									{
										if (colResult->changeVelEffectObj0->mask[0])
										{
											if (colResult->changeVelEffectObj0->value.x*object0->vel.x < 0)
											{
												colResult->changeVelEffectObj0->value.x = -object0->vel.x;
											} else{
												colResult->changeVelEffectObj0->value.x = 0;

											}
										}
										if (colResult->changeVelEffectObj0->mask[1])
										{
											if (colResult->changeVelEffectObj0->value.y*object0->vel.y < 0)
											{
												colResult->changeVelEffectObj0->value.y = -object0->vel.y;
											} else{
												colResult->changeVelEffectObj0->value.y = 0;
											}
										}
										if (colResult->changeVelEffectObj0->mask[2])
										{
											if (colResult->changeVelEffectObj0->value.z*object0->vel.z < 0)
											{
												colResult->changeVelEffectObj0->value.z = -object0->vel.z;
											} else{
												colResult->changeVelEffectObj0->value.z = 0;
											}
										}

									} else if (object0->boundingStructure->isImmovable)
									{
										if (colResult->changeVelEffectObj1->mask[0])
										{
											if (colResult->changeVelEffectObj1->value.x*object1->vel.x < 0)
											{
												colResult->changeVelEffectObj1->value.x = -object1->vel.x;
											} else{
												colResult->changeVelEffectObj1->value.x = 0;
											}
										}
										if (colResult->changeVelEffectObj1->mask[1])
										{
											if (colResult->changeVelEffectObj1->value.y*object1->vel.y < 0)
											{
												colResult->changeVelEffectObj1->value.y = -object1->vel.y;
											} else{
												colResult->changeVelEffectObj1->value.y = 0;
											}
										}
										if (colResult->changeVelEffectObj1->mask[2])
										{
											if (colResult->changeVelEffectObj1->value.z*object1->vel.z < 0)
											{
												colResult->changeVelEffectObj1->value.z = -object1->vel.z;
											} else{
												colResult->changeVelEffectObj1->value.z = 0;
											}
										}

									} else
									{
                                        /*colResult->changeVelEffectObj0->mask[0] = false;
                                        colResult->changeVelEffectObj0->mask[1] = false;
                                        colResult->changeVelEffectObj0->mask[2] = false;

                                        colResult->changeVelEffectObj1->mask[0] = false;
                                        colResult->changeVelEffectObj1->mask[1] = false;
                                        colResult->changeVelEffectObj1->mask[2] = false;*/

                                        float invMasses = 1.0/(object0->mass+object1->mass);
                                        float vel0 = object0->vel.GetNorm();
                                        float vel1 = object1->vel.GetNorm();
                                        float coeff = 1;

                                        float v0final = coeff*( (vel0*(object0->mass-object1->mass)*invMasses)+ (vel1*(2.0*object1->mass)*invMasses) );
                                        float v1final = coeff*((vel1*(object1->mass-object0->mass)*invMasses)+ (vel0*(2.0*object0->mass)*invMasses));

                                        colResult->changeVelEffectObj0->value.MulScalar(v0final);
                                        colResult->changeVelEffectObj1->value.MulScalar(v1final);
                                        //mjVector3 obj0Obj1(object1.pos);

                                        //obj0Obj1.Subtract(object0.pos);

                                        //obj0Obj1.Normalize();

                                        //colResult->accelObj0 = new mjPhysicsEffect(MJ_COLLISION, MJ_ADD_FORCE);
                                        //colResult->accelObj0->value.ScaleAdd(object1->mass, object1.vel);

                                        //colResult->accelObj0->value;

									}




									colResult->relocationEffectObj0->otherObject = object1;
									colResult->changeVelEffectObj0->otherObject = object1;
									object0->collisionStack.push_back(colResult->relocationEffectObj0);
									object0->collisionStack.push_back(colResult->changeVelEffectObj0);

									colResult->relocationEffectObj1->otherObject = object0;
									colResult->changeVelEffectObj1->otherObject = object0;
									object1->collisionStack.push_back(colResult->relocationEffectObj1);
									object1->collisionStack.push_back(colResult->changeVelEffectObj1);

                                    object0->OnOverlap(object1);
                                    object1->OnOverlap(object0);

									//LOGI("changeVel: %3.3f, %3.3f, %3.3f", colResult->changeVelEffectObj1->value.x, colResult->changeVelEffectObj1->value.y, colResult->changeVelEffectObj1->value.z);

									/*if (colResult->changeVelEffectObj1->value.Check(__FILE__, __LINE__))
							{
								LOGI("CEff: 0x%x, otherObj: 0x%x", colResult->changeVelEffectObj1, colResult->changeVelEffectObj1->otherObject);
							}
							if (colResult->changeVelEffectObj0->value.Check(__FILE__, __LINE__))
							{
								LOGI("CEff: 0x%x, otherObj: 0x%x", colResult->changeVelEffectObj0, colResult->changeVelEffectObj0->otherObject);
							}*/
									//FIXME:!!! Something must be done with colResult in this case
									// without altering the inner effects, since those will be destroyed in the object after they'be been used.

								}else
								{

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
						delete colResult; // Delete the collision result whether it has been used or not.

					}

				}

			}
		}
	}
}
void mjPhysics::ProcessPhysicsEffectsAndUpdate(float t_elapsed)
{
	mjPhysicsEffect gravityEffect(MJ_GRAVITY, MJ_ADD_ACCEL);
	gravityEffect.value.CopyFrom(gravity);

	for(unsigned i = 0; i < allObjects.size(); i++)
	{
		if (allObjects[i]->hasKinematics)
		{



			allObjects[i]->effectStack.push_back(&gravityEffect);

			for (unsigned j = 0; j < globalEffects.size(); j++)
            {
				//if (allObjects[i]->)
				//{
					allObjects[i]->effectStack.push_back(globalEffects[j]);
				//}
            }

			allObjects[i]->ProcessPhysicsEffects(t_elapsed);
		}


		allObjects[i]->Update(t_elapsed);

	}

	for (unsigned j = 0; j < globalEffects.size(); j++)
    {
		delete globalEffects[j];

    }
    globalEffects.clear();

}
void mjPhysics::ProcessCollisionEffects()
{
	for(unsigned i = 0; i < allObjects.size(); i++)
	{
		if (allObjects[i]->hasKinematics){
			allObjects[i]->ProcessCollisionEffects();
		}
		for (unsigned j = 0; j < allObjects[i]->collisionStack.size(); j++)
		{
            delete allObjects[i]->collisionStack[j];

		}
		allObjects[i]->collisionStack.clear();
	}

}
void mjPhysics::UpdatePositions(float t_elapsed)
{
	for(unsigned i = 0; i < allObjects.size(); i++)
	{
		if (allObjects[i]->hasKinematics){
			allObjects[i]->UpdatePosition(t_elapsed);
		}
	}

}
}
