#ifndef KEYBOARDCONTROL_H
#define KEYBOARDCONTROL_H

#include <extLibs/util/mjMultiPlatform.h>
#include <core/mjVector3.h>

using namespace mjEngine;

#define KEYTIME_RUN 0.4

class KeyboardControl
{
    public:
        KeyboardControl();

        bool keysDown[4];
        bool allKeysLetGo = false;
        bool cameraControl = false;

        bool jumpKeyState = false;
        bool jumpKeyEvent = false;


        void Update(float t_elapsed);
        float arrowKeysTimeHeld = 0;
        void HandleSDLKeyboardEvent(SDL_KeyboardEvent& keyEvent);
        void GetJoystickValues(mjVector3* lJoystick, mjVector3* rJoystick);
        virtual ~KeyboardControl();

    protected:
    private:
};

#endif // KEYBOARDCONTROL_H
