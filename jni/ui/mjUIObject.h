#ifndef MJUIOBJECT_H
#define MJUIOBJECT_H

#include "../core/mjObject.h"

namespace mjEngine {

//! The objective behind a mjUIObject is to be able to easily "poke" a mjObject and have it send messages
//! And that most of the boilerplate code is already here.
class mjUIObject : public mjObject
{
public:

    //! whether or not it is actually poke-able.
    bool isPokeable = true;
    //! Determines the size of the rectangular area around the centre that can be activated
    mjVector3 hitboxSize;
    //! The message to be sent via the internal messaging system when poked
    std::string message;


    mjUIObject(mjResourceManager* resourceManager, structuretype collisionStructureType = MJ_NO_BOUNDING_STRUCT);

    //! X and Y should be sent in pseudo-normalised screen coordinates. Where the smallest dimension is mapped from [-1 .. 1]
    //! and the bigger dimension can go beyond -1/1 to conserve aspect ratio.
    //! For example, for a 1024x768 screen, the VERTICAL coordinates would go from -1 to 1 (e.g. for a Y of 767, the equivalent in
    //! pseudo-normalised coordinates would be -1 while 0 would be 1 in pseudo-normalised coordinates).
    //! The HORIZONTAL coordinates would go somewhat beyond -1 and 1.
    //!
    //! The function must return whether or not it was poked
    virtual bool TestPoke(float x, float y);
    void SetDetailsFromXML(XMLElement* entity) override;
};

}
#endif // MJUIOBJECT_H
