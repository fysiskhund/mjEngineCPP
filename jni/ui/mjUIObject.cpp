#include "mjUIObject.h"
namespace mjEngine {


mjUIObject::mjUIObject(mjResourceManager* resourceManager, structuretype collisionStructureType)
    :mjObject(resourceManager, collisionStructureType)
{
    this->resourceManager = resourceManager;
    // that's about it?
}

bool mjUIObject::TestPoke(float x, float y)
{
    if (isPokeable)
    {
        // For now, things are expected to be just rectangular. If the point is inside the
        // rectangle, it returns true.
        // the SCALE property defines the size of the rectangle.

        if ((fabs(x-pos.x) <= 0.5*hitboxSize.x) && (fabs(y-pos.y) < 0.5*hitboxSize.y))
        {
            CastMessage((void*) this, (void*) message.c_str(), 0, 0);
            return true;
        }
    }
    return false;
}

void mjUIObject::SetDetailsFromXML(XMLElement* entity)
{
    mjObject::SetDetailsFromXML(entity);

    const char* value;

    // Read its characteristics

    // Attributes
    value = entity->Attribute("message");
    if (value)
    {
        this->message = value;
    } else
    {
        this->message = id;
        this->message += ".poked";
    }
}

}
