#include "Character.h"

Character::Character(mjResourceManager& resourceManager)
: mjObject(MJ_AABB)
{
	SetUpSillyAnimation();
	model = resourceManager.FetchModel("char0.mesh.xml");
	mjAABB* charBoundStruct = (mjAABB*) boundingStructure;
	mjVector3 minCorner;
	minCorner.Set(-0.3,0,-0.3);
	mjVector3 maxCorner;
	maxCorner.Set(0.3,1.65, 0.3);
	charBoundStruct->SetCorners(minCorner,maxCorner);





	GLuint glTexture = resourceManager.FetchTexture("suit_test.png");
	for (unsigned i = 0; i < model->meshes.size(); i++)
	{
		model->meshes[i]->glTexture = glTexture;
	}
	mass = 55;
}

void Character::ProcessPhysicsEffects(float t_elapsed)
{
	accel.Set0();

	for (unsigned i = 0; i < effectStack.size(); i++)
	{
		switch(effectStack[i]->type)
		{
			case MJ_ACCELERATION:
			case MJ_GRAVITY:
				accel.Add(effectStack[i]->value);

			break;
			case MJ_FORCE:
                if (effectStack[i]->value.GetNorm() > 3)
                {
                    accel.ScaleAdd(1.0/mass, effectStack[i]->value);
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
void Character::ProcessCollisionEffects()
{

	int previousFootingValue = footing;
	footing = 0;

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
			if (gravity) // If gravity is set..
			{
				mjVector3 maskDirection;

				maskDirection.Set(collisionEffect->mask[0], collisionEffect->mask[1], collisionEffect->mask[2]);


				maskDirection.Normalize();

				mjVector3 gravityNormalized;
				gravityNormalized.CopyFrom(*gravity);
				gravityNormalized.Normalize();
				if (gravityNormalized.Dot(maskDirection) < -0.4)
				{
					if (!previousFootingValue)
					{
						//LOGI("char: footing -> yes");


					}
					footing = 1;
					objectProvidingFooting = collisionEffect->otherObject;
				} else {
                    //LOGI("noFooting");
				}
			}
			break;
		default:
			//whatever
			break;
		}
	}

	if (previousFootingValue && (footing == 0))
	{
		//LOGI("char: footing -> *no*");
	}


	mjObject::ProcessCollisionEffects();


}
void Character::Update(float t_elapsed)
{




	if (gravity)
	{
		if (jumping)
		{

			jumping = 0;
			footing = 0;
			if (vel.GetNorm() < gravity->GetNorm()*100.0)
			{
				//LOGI("Vel: %3.3f, %3.3f, %3.3f", vel.x, vel.y, vel.z);
				vel.ScaleAdd(-0.64, *gravity);
			}
			LOGI("char: footing -> no (jumping)");
		}
	}
	float intrinsecVelNorm = intrinsecVel.GetNorm();
	if (intrinsecVelNorm < 10 && footing)
    {

        if ((intrinsecVel.x*vel.x < 0))// || fabs(intrinsecVel.x + vel.x) < MAX_VEL_FOR_CHARACTER)
        {
            vel.x += intrinsecVel.x;
        }


        if ((intrinsecVel.y*vel.y < 0))// || fabs(intrinsecVel.y + vel.y) < MAX_VEL_FOR_CHARACTER)
        {
            vel.y += intrinsecVel.y;
        }

        if ((intrinsecVel.z*vel.z < 0))// || fabs(intrinsecVel.z + vel.z) < MAX_VEL_FOR_CHARACTER)
        {
            vel.z += intrinsecVel.z;
        }
    }

	if (intrinsecVelNorm > 0.01)
	{
		tAnimation += t_elapsed*intrinsecVelNorm;

			if (tAnimation > 2)
				tAnimation -= 2;

			pose->angles[0]->x = intrinsecVelNorm*0.01*1.5707; // inclination when running

			animator.UpdatePose(tAnimation, *pose, animation);
	} else
	{
		tAnimation = 0; // Reset animation
		animator.UpdatePose(tAnimation, *pose, animation);
	}

    vel.MulScalar(0.99);

	mjObject::Update(t_elapsed);


}
void Character::UpdatePosition(float t_elapsed)
{

    if (intrinsecVel.GetNorm() < 10)
    {

        pos.ScaleAdd(t_elapsed, intrinsecVel);
    }

    if (footing)
    {
        pos.ScaleAdd(t_elapsed, objectProvidingFooting->vel);
        /*if (fabs(vel.x) < fabs(objectProvidingFooting->vel.x))
        {
            vel.x = objectProvidingFooting->vel.x;
        }
        if (fabs(vel.y) < fabs(objectProvidingFooting->vel.y))
        {
            vel.y = objectProvidingFooting->vel.y;
        }
        if (fabs(vel.z) < fabs(objectProvidingFooting->vel.z))
        {
            vel.z = objectProvidingFooting->vel.z;
        }*/
    }

	mjObject::UpdatePosition(t_elapsed);

}

void Character::Check()
{
	if (pos.GetNorm() > 15)
	{
		LOGI("Weird position %3.3f, %3.3f, %3.3f", pos.x, pos.y, pos.z);
	}
}
void Character::SetDetailsFromXML(XMLElement* entity)
{
    mjObject::SetDetailsFromXML(entity);
    startPosition.CopyFrom(pos);

    mjAABB* mjaabbStruct = (mjAABB*) boundingStructure;
    mjaabbStruct->UpdateCorners();
}

void Character::SetUpSillyAnimation()
{
	//Animation test
	    mjAnimationSegment* segment0 = new mjAnimationSegment();
	    segment0->meshNum = 0;
	    segment0->totalTime = 0.5;

	    mjAnimationKeyframe* keyframe0 = new mjAnimationKeyframe();

	    // Keyframe0 and 2 are simply the normal pose
	    keyframe0->timeStamp = 0;

	    mjAnimationKeyframe* keyframe1 = new mjAnimationKeyframe();

	    // Keyframe1 is a slight hop
	    keyframe1->pos.y = 0.03;
	    keyframe1->timeStamp = 0.25;

	    mjAnimationKeyframe* keyframe2 = new mjAnimationKeyframe();


	    keyframe2->timeStamp = 0.5;



	    segment0->keyframes.push_back(keyframe0);
	    segment0->keyframes.push_back(keyframe1);
	    segment0->keyframes.push_back(keyframe2);

	    animation.segments.push_back(segment0);

	    pose = new mjModelPose();
	    pose->angles.push_back(new mjVector3());
	    pose->positions.push_back(new mjVector3());

	    pose->angles.push_back(new mjVector3());
	    pose->positions.push_back(new mjVector3()); // As many "angles" and "positions" as the number of meshes the model has!


	//////////// end of animation test (init)
}
