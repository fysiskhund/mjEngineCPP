/*
 * Copyright (C) 2014-2016 Alejandro Valenzuela Roca
 * 
 */

package co.phong.takkatakka;

import android.content.res.AssetManager;

// Wrapper for native library

public class GL2JNILib {

     static {
         System.loadLibrary("mjGame");
     }

    /**
     * @param width the current view width
     * @param height the current view height
     */
     public static native void init(int width, int height, String jPathPrefix, AssetManager assetManager);
     public static native boolean step(float t_elapsed);
     
     
     public static native byte[] HandleEngineQuery();     
     public static native void HandleJoystickInput(int controllerID, int joystickID, float x, float y);
     public static native void HandleButtonInput(int controllerID, int buttonID, boolean pressedDown);
     public static native void HandleTouchInput(int fingerID, boolean pressedDown, float x, float y);
     public static native void SendEngineQuery(String cmdStr);
     
     public static boolean isReady = false;
}
