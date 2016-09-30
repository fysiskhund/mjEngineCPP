#ifndef MJINPUTEVENT_H
#define MJINPUTEVENT_H

namespace mjEngine {

// These numerical values and comments are basically stolen from SDL, for practical reasons.
//
enum MJInputTypes
{
    MJ_EVENT_NONE,

    /* Application events */
    MJ_QUIT           = 0x100, /**< User-requested quit */

    /* These application events have special meaning on iOS, see README-ios.md for details */
    MJ_APP_TERMINATING,        /**< The application is being terminated by the OS
                                     Called on iOS in applicationWillTerminate()
                                     Called on Android in onDestroy()
                                */
    MJ_APP_LOWMEMORY,          /**< The application is low on memory, free memory if possible.
                                     Called on iOS in applicationDidReceiveMemoryWarning()
                                     Called on Android in onLowMemory()
                                */
    MJ_APP_WILLENTERBACKGROUND, /**< The application is about to enter the background
                                     Called on iOS in applicationWillResignActive()
                                     Called on Android in onPause()
                                */
    MJ_APP_DIDENTERBACKGROUND, /**< The application did enter the background and may not get CPU for some time
                                     Called on iOS in applicationDidEnterBackground()
                                     Called on Android in onPause()
                                */
    MJ_APP_WILLENTERFOREGROUND, /**< The application is about to enter the foreground
                                     Called on iOS in applicationWillEnterForeground()
                                     Called on Android in onResume()
                                */
    MJ_APP_DIDENTERFOREGROUND, /**< The application is now interactive
                                     Called on iOS in applicationDidBecomeActive()
                                     Called on Android in onResume()
                                */

    /* Window events */
    MJ_WINDOWEVENT    = 0x200, /**< Window state change */
    MJ_SYSWMEVENT,             /**< System specific event */

    /* Keyboard events */
    MJ_KEYDOWN        = 0x300, /**< Key pressed */
    MJ_KEYUP,                  /**< Key released */
    MJ_TEXTEDITING,            /**< Keyboard text editing (composition) */
    MJ_TEXTINPUT,              /**< Keyboard text input */
    MJ_KEYMAPCHANGED,          /**< Keymap changed due to a system event such as an
                                     input language or keyboard layout change.
                                */

    /* Mouse events */
    MJ_MOUSEMOTION    = 0x400,
    MJ_MOUSEBUTTONDOWN,
    MJ_MOUSEBUTTONUP,
    MJ_MOUSEWHEEL,

    /* Joystick events */
    MJ_JOYAXISMOTION  = 0x600, /**< Joystick axis motion */
    MJ_JOYBALLMOTION,          /**< Joystick trackball motion */
    MJ_JOYHATMOTION,           /**< Joystick hat position change */
    MJ_JOYBUTTONDOWN,          /**< Joystick button pressed */
    MJ_JOYBUTTONUP,            /**< Joystick button released */
    MJ_JOYDEVICEADDED,         /**< A new joystick has been inserted into the system */
    MJ_JOYDEVICEREMOVED,       /**< An opened joystick has been removed */

    /* Game controller events */
    MJ_CONTROLLERAXISMOTION  = 0x650, /**< Game controller axis motion */
    MJ_CONTROLLERBUTTONDOWN,          /**< Game controller button pressed */
    MJ_CONTROLLERBUTTONUP,            /**< Game controller button released */
    MJ_CONTROLLERDEVICEADDED,         /**< A new Game controller has been inserted into the system */
    MJ_CONTROLLERDEVICEREMOVED,       /**< An opened Game controller has been removed */
    MJ_CONTROLLERDEVICEREMAPPED,      /**< The controller mapping was updated */

    /* Touch events */
    MJ_FINGERDOWN      = 0x700,
    MJ_FINGERUP,
    MJ_FINGERMOTION,


};

class mjInputEvent
{
public:
    MJInputTypes type = MJ_EVENT_NONE;
    float time;

    int mouseButtonNumber;
    int mouseButtonState;
    int keyboardKey;
    int keyboardKeyState;

    mjInputEvent();


};

}
#endif // MJINPUTEVENT_H
