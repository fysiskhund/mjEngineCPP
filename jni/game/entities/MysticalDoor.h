#ifndef MYSTICALDOOR_H
#define MYSTICALDOOR_H

#include <string>

#include <extLibs/util/mjMultiPlatform.h>


#include <core/mjObject.h>
#include <util/mjResourceManager.h>
#include <graphics/mjImageLoader.h>

#include <game/Level.h>

using namespace mjEngine;


class MysticalDoor: public mjObject
{
    public:

        std::string counterpartName;
        MysticalDoor* counterpart = NULL;
        mjVector3 offsetOnTeleportArrive;

        MysticalDoor(Level* levelData, mjResourceManager* resourceManager);
        void SetDetailsFromXML(XMLElement* entity) override;

        virtual ~MysticalDoor();
    protected:
    private:
};

#endif // MYSTICALDOOR_H
