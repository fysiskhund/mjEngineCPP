#ifndef MYSTICALDOOR_H
#define MYSTICALDOOR_H

#include <string>

#include <extLibs/util/mjMultiPlatform.h>


#include <core/mjObject.h>
#include <util/mjResourceManager.h>
#include <graphics/mjImageLoader.h>

using namespace mjEngine;


class MysticalDoor: public mjObject
{
    public:

        std::string counterpartName;
        MysticalDoor* counterpart;

        MysticalDoor(mjResourceManager* resourceManager);
        virtual ~MysticalDoor();
    protected:
    private:
};

#endif // MYSTICALDOOR_H
