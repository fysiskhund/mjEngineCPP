#include "FallingBox.h"

FallingBox::FallingBox(mjResourceManager& resourceManager)
:Box(resourceManager)
{
    //ctor
}

void FallingBox::SetDetailsFromXML(XMLElement* fallingBoxElem)
{
    mjObject::SetDetailsFromXML(fallingBoxElem);
    startPosition.CopyFrom(pos);
}


void FallingBox::ProcessCollisionEffects()
{
    hasWeight = false;
    for (unsigned i=0; i < collisionStack.size(); i++)//(mjPhysicsEffect collisionEffect:collisionStack)
    {
        mjPhysicsEffect* collisionEffect = collisionStack[i];

        if ((collisionEffect->otherObject) && collisionEffect->otherObject->mass >= 30)
        {

            switch(collisionEffect->action)
            {
            case MJ_ADD_VELOCITY:
                {
                    if (collisionEffect->value.Dot(gravity)< -0.1)
                    {
                        hasWeight = true;
                    }
                }
                break;
            default:
                break;
            }
        }
    }
    Box::ProcessCollisionEffects()
}

void FallingBox::Update(float t_elapsed)
{
    if (hasWeight)
    {
        timeToFall += t_elapsed;
    }
    if (timeToFall > totalTimeToFall)
    {
        // Get affected by gravity "manually"
        isImmovable = false;
    }
    Box::Update(t_elapsed);
    isImmovable = true;
}


FallingBox::~FallingBox()
{
    //dtor
}
