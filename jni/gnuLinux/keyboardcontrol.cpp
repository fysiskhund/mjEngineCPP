#include "keyboardcontrol.h"

KeyboardControl::KeyboardControl()
{
    //ctor
}

void KeyboardControl::HandleSDLKeyboardEvent(SDL_KeyboardEvent& keyEvent)
{


    switch (keyEvent.type)
    {

        case SDL_KEYDOWN:
            switch(keyEvent.keysym.sym)
            {
            case SDLK_f:
                fullScreen = ! fullScreen;
            break;
            case SDLK_UP:
                keysDown[0] = true;
            break;
            case SDLK_LEFT:
                keysDown[1] = true;
            break;
            case SDLK_DOWN:
                keysDown[2] = true;
            break;
            case SDLK_RIGHT:
                keysDown[3] = true;
            break;
            case SDLK_SPACE:
                jumpKeyState = true;
                jumpKeyEvent = true;
                break;
            }
        break;
        case SDL_KEYUP:
            switch(keyEvent.keysym.sym)
            {
            case SDLK_UP:
                keysDown[0] = false;
            break;
            case SDLK_LEFT:
                keysDown[1] = false;
            break;
            case SDLK_DOWN:
                keysDown[2] = false;
            break;
            case SDLK_RIGHT:
                keysDown[3] = false;
            break;
            case SDLK_SPACE:
                jumpKeyState = false;
                jumpKeyEvent = true;
                break;
            }

            // find out when all keys are let go.

            allKeysLetGo = ((!keysDown[0]) && ((keysDown[0] == keysDown[1]) && (keysDown[1] == keysDown[2]) && (keysDown[2] == keysDown[3]) && (keysDown[3] == keysDown[4])));
        break;
    }
    if (keyEvent.keysym.mod&KMOD_CTRL)
    {
        if (!cameraControl)
        {
            allKeysLetGo = true;
            cameraControl = true;
        }


    } else
    {
        if (cameraControl)
        {
            allKeysLetGo = true;
            cameraControl = false;
        }

    }

}

void KeyboardControl::Update(double t_elapsed)
{
    if (keysDown[0] || keysDown[1] || keysDown[2] || keysDown[3])
    {
        arrowKeysTimeHeld += t_elapsed;
        if (arrowKeysTimeHeld > KEYTIME_RUN)
        {
            arrowKeysTimeHeld = KEYTIME_RUN;
        }
    } else
    {
        arrowKeysTimeHeld = 0;
    }
    jumpKeyEvent = false;
}

void KeyboardControl::GetJoystickValues(mjVector3* lJoystick, mjVector3* rJoystick)
{
    mjVector3* whichJoystick = lJoystick;
    if (cameraControl)
    {
        lJoystick->Set0();
        whichJoystick = rJoystick;
    }
    if (keysDown[0] || keysDown[1] || keysDown[2] || keysDown[3])
    {
        rJoystick->Set0();
        whichJoystick->Set0();
        if (keysDown[0])
        {
            whichJoystick->y = -1;
        } else if (keysDown[2])
        {
            whichJoystick->y = 1;
        }

        if (keysDown[1])
        {
            whichJoystick->x = -1;
        } else if (keysDown[3])
        {
            whichJoystick->x = 1;
        }
        whichJoystick->Normalize();
        whichJoystick->MulScalar((float)(arrowKeysTimeHeld/(float)KEYTIME_RUN));
    } else if (allKeysLetGo)
    {
        whichJoystick->Set0();
    }
    allKeysLetGo = false;

}

KeyboardControl::~KeyboardControl()
{
    //dtor
}
