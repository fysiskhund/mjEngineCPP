#include "FallingBox.h"

FallingBox::FallingBox(mjResourceManager* resourceManager)
:Box(resourceManager)
{
    useModelFromXMLDetails = true;
    checkGlError("useModelFromXML");

    gravity.Set(0, -9.81, 0);

    travelDirection.Set(0, -1,0);

    GLuint glTexture;

    glTexture = resourceManager->FetchTexture("falling_box.png", GL_CLAMP_TO_EDGE);
    model = resourceManager->FetchModel("fallingbox.mesh.xml");


    mjAABB* boundingStruct = ((mjAABB*)boundingStructure);

    boundingStruct->isImmovable = true;




    for (unsigned i = 0; i<model->meshes.size(); i++)
    {
        model->meshes[i]->glTexture = glTexture;
    }
    hasKinematics = true;


    cinderBlockSlide.Load(resourceManager->FetchSound("sounds/95000__j1987__cinderblockmove_mono.wav"),0);

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

    XMLElement* timingElement;

    timingElement = fallingBoxElem->FirstChildElement("totaltimetofall");
    if (timingElement)
    {
    	timingElement->QueryFloatAttribute("value", &this->totalTimeToFall);
    }

    timingElement = fallingBoxElem->FirstChildElement("totaltimetoreturn");
    if (timingElement)
    {
        timingElement->QueryFloatAttribute("value", &this->totalTimeToReturn);
    }

    /////// Travelling box test
    XMLElement* controlPointElement = fallingBoxElem->FirstChildElement("controlpoint");
    if (controlPointElement)
    {
        // The very start position is always added first
        controlPoints.push_back(&startPosition);

        mjVector3* previousControlPoint = &startPosition;
        while (controlPointElement)
        {
            mjVector3* cPointVector = new mjVector3();
            mjXMLHelper::ReadVector(controlPointElement, cPointVector);
            bool isRelativeToPreviousPosition = false;
            controlPointElement->QueryBoolAttribute("isrelative", &isRelativeToPreviousPosition);

            if ( isRelativeToPreviousPosition)
            {
                cPointVector->Add(*previousControlPoint);
            }

            controlPoints.push_back(cPointVector);

            previousControlPoint = cPointVector;

            controlPointElement = controlPointElement->NextSiblingElement();

        }
    }

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

                    Reset();
                }
                // Select next control point
                currentControlPointIndex++;

                if (currentControlPointIndex >= controlPoints.size())
                {
                	if (totalTimeToReturn < 0)
                	{
                		active = false; // The box never returns
                	} else
					{
                		if (timeToReturn < totalTimeToReturn )
                		{
                			currentControlPointIndex = controlPoints.size()-1; // Keep box in current control point
                			timeToReturn += t_elapsed;
                		} else
                		{
                			currentControlPointIndex = 0;
                		}

					}

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
                        //LOGI("Has weight");
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
        if ((timeToFall >= totalTimeToFall-1.4) && !slidingSoundPlaying)
        {
            // Play the sound effect when the box is close to falling
            cinderBlockSlide.Play(this->pos, 0);
            slidingSoundPlaying = true;
        }
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
    // If the box must fall after first contact
    // then this hasWeight variable isn't set to false until the box is reset.
    if (timeToFallIsAccumulative)
    {
        hasWeight = false;
    }


    mjVector3 startToCurrentPos(pos);
    startToCurrentPos.Subtract(startPosition);
    if (startToCurrentPos.GetNormSquared() > 6400)
    {
        Reset();

    }
}

void FallingBox::Reset()
{
    vel.Set0();
    timeToFall = 0;
    pos.CopyFrom(startPosition);
    active = false;
    hasWeight = false;
    slidingSoundPlaying = false;
}


FallingBox::~FallingBox()
{
    //dtor
}
