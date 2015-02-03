/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 * 
 */

package co.phong.mjengine;

// Wrapper for native library

public class GL2JNILib {

     static {
         System.loadLibrary("mjengine");
     }

    /**
     * @param width the current view width
     * @param height the current view height
     */
     public static native void init(int width, int height, String jPathPrefix);
     public static native boolean step(float t_elapsed);
     
     
     public static native byte[] HandleEngineQuery();     
     public static native void HandleJoystickInput(int controllerID, int joystickID, float x, float y);
     public static native void HandleButtonInput(int controllerID, int buttonID, boolean pressedDown);
}
