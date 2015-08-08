#ifndef MYSTICALDOOR_H
#define MYSTICALDOOR_H

#include <string>

#include <extLibs/util/mjMultiPlatform.h>


#include <core/mjObject.h>
#include <util/mjResourceManager.h>
#include <graphics/mjImageLoader.h>
#include <physics/mjCollisionTests.h>

#include "../Level.h"


#include "KosmoObject.h"

using namespace mjEngine;


class MysticalDoor: public KosmoObject
{
    public:

        std::string counterpartName;
        MysticalDoor* counterpart = NULL;
        bool teleportFunctionActive = true;
        bool isCheckpointForPlayer = true;
        mjVector3 offsetOnTeleportArrive;
        float offsetRadiusOnTeleportArrive;

        MysticalDoor(Level* levelData, mjResourceManager* resourceManager);
        void SetDetailsFromXML(XMLElement* entity) override;
        void ProcessCollisionEffects() override;

        void DEBUGonCollisionTestStart(mjObject* otherObject) override;
        void OnOverlap(mjObject* otherObject) override;

        virtual ~MysticalDoor();
    protected:
    private:
};

#endif // MYSTICALDOOR_H
