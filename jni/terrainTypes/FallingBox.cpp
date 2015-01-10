#include "FallingBox.h"

FallingBox::FallingBox(mjResourceManager& resourceManager)
:Box(resourceManager)
{
    gravity.Set(0, -9.81, 0);

    travelDirection.Set(0, -1,0);

    model = resourceManager.FetchModel("fallingbox.mesh.xml");

    mjAABB* boundingStruct = ((mjAABB*)boundingStructure);
    boundingStruct->isImmovable = true;


    GLuint glTexture = resourceManager.FetchTexture("falling_box.png");

    for (unsigned i = 0; i<model->meshes.size(); i++)
    {
        model->meshes[i]->glTexture = glTexture;
    }
    hasKinematics = true;



}

void FallingBox::SetDetailsFromXML(XMLElement* fallingBoxElem)
{
    mjObject::SetDetailsFromXML(fallingBoxElem);
    mjXMLHelper::ReadVector(fallingBoxElem->FirstChildElement("gravity"), &gravity);

    ((mjAABB*) boundingStructure)->UpdateCenter();
    startPosition.CopyFrom(pos);
    gravityNormalized.CopyFrom(gravity);
    gravityNormalized.Normalize();
    hasWeight = false;



    /////// Travelling box test
    controlPoints.push_back(&startPosition);

    mjVector3* point1 = new mjVector3();
    point1->CopyFrom(startPosition);
    point1->y += 16;
    controlPoints.push_back(point1);
}

void FallingBox::ProcessPhysicsEffects(float t_elapsed)
{
	Box::ProcessPhysicsEffects(t_elapsed);

	if (active)
	{
        if (controlPoints.size() > 0)
        {
            // Select the control point we're travelling to


            travelDirection.CopyFrom(*controlPoints[currentControlPointIndex]);
            travelDirection.Subtract(pos);
            if (travelDirection.Normalize() < 0.1)
            {

                vel.Set0();

                if ((currentControlPointIndex == 0) && !hasWeight)
                {
                        // Reset the box,
                        //FIXME: add a behaviour switch whether the box should continue on its own or wait for the player again.
                        // By default, wait for the player.

                    timeToFall = 0;
                    pos.CopyFrom(startPosition);
                    active = false;
                }
                // Select next control point
                currentControlPointIndex++;

                if (currentControlPointIndex >= controlPoints.size())
                {
                    currentControlPointIndex = 0;
                }
            }


        }
            // Start falling using the established travel direction
            vel.ScaleAdd(t_elapsed, travelDirection);

	}
}


void FallingBox::ProcessCollisionEffects()
{

    for (unsigned i=0; i < collisionStack.size(); i++)//(mjPhysicsEffect collisionEffect:collisionStack)
    {
        mjPhysicsEffect* collisionEffect = collisionStack[i];

        if ((collisionEffect->otherObject) && collisionEffect->otherObject->mass >= 30)
        {

            switch(collisionEffect->action)
            {
            case MJ_ADD_VELOCITY:
                {
                    if (collisionEffect->value.Dot(gravityNormalized)> 0.9) //pretty much the same angle
                    {
                        hasWeight = true;
                        LOGI("Has weight");
                    }
                }
                break;
            default:
                break;
            }
        }
    }
    Box::ProcessCollisionEffects();
}

void FallingBox::Update(float t_elapsed)
{
    if (hasWeight)
    {
        timeToFall += t_elapsed;
        //LOGI("Accumulated time: %3.3f", timeToFall);
        if (timeToFall > totalTimeToFall)
        {
            active = true;
        }
    }

    Box::Update(t_elapsed);
    //hasKinematics = false;

    // hasWeight must be updated per-frame.
    hasWeight = false;

    if (pos.GetNormSquared() > 40000)
    {
        vel.Set0();
        timeToFall = 0;
        pos.CopyFrom(startPosition);
        active = false;
    }
}


FallingBox::~FallingBox()
{
    //dtor
}
