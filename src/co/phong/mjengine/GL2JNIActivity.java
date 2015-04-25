/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package co.phong.mjengine;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.WindowManager;

import java.io.File;


public class GL2JNIActivity extends Activity {

    GL2JNIView mView;

    @Override protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        /*try {
			Thread.sleep(3000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}*/
        mView = new GL2JNIView(getApplication());
        setContentView(mView);
    }

    @Override protected void onPause() {
        super.onPause();
        Log.i("mjEngine_J", "App is paused");
        mView.onPause();
        mjJNICommandInterpreter.musicPlayer.pause();
    }

    @Override protected void onResume() {
        super.onResume();
        Log.i("mjEngine_J", "App is resumed");
        mView.onResume();
        mjJNICommandInterpreter.musicPlayer.start(); // (this resumes playback)
    }
    @Override
    public boolean onTouchEvent(MotionEvent e) {
        // MotionEvent reports input details from the touch screen
        // and other input controls. In this case, you are only
        // interested in events where the touch position changed.

        float x = e.getX();
        float y = e.getY();

        switch (e.getAction()) {
            case MotionEvent.ACTION_MOVE:


        }

        return true;
    }
    @Override public boolean dispatchGenericMotionEvent(MotionEvent event)
    {


    	InputDevice controllerDevice = event.getDevice();
    	if ((controllerDevice.getSources() & InputDevice.SOURCE_CLASS_JOYSTICK) != 0) {

    		int controllerID = controllerDevice.getId();
    		if (GL2JNILib.isReady){
    			switch(event.getAction())
    			{
    			case MotionEvent.ACTION_MOVE:
    				float x0, y0;
    				float x1, y1;
    				for (int i = 0; i < event.getHistorySize(); i++)
    				{
    					x0 = event.getHistoricalAxisValue(MotionEvent.AXIS_X, i);
    					y0 = event.getHistoricalAxisValue(MotionEvent.AXIS_Y, i);
    					GL2JNILib.HandleJoystickInput(controllerID, 0, x0, y0);

    					x1 = event.getHistoricalAxisValue(MotionEvent.AXIS_Z, i);
    					y1 = event.getHistoricalAxisValue(MotionEvent.AXIS_RZ, i);
    					GL2JNILib.HandleJoystickInput(controllerID, 1, x1, y1);
    				}

    				x0 = event.getAxisValue(MotionEvent.AXIS_X); 
    				y0 = event.getAxisValue(MotionEvent.AXIS_Y);
    				GL2JNILib.HandleJoystickInput(controllerID, 0, x0, y0);

    				x1 = event.getAxisValue(MotionEvent.AXIS_Z);
    				y1 = event.getAxisValue(MotionEvent.AXIS_RZ);

    				GL2JNILib.HandleJoystickInput(controllerID, 1, x1, y1);

    				return true;
    			default:
    				break;
    			}
    		}

    	
        	
        } 
    	return super.dispatchGenericMotionEvent(event);
    }
    
    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
    	
    	
    	
    	if (KeyEvent.isGamepadButton(event.getKeyCode()))
    	{
    		
    		if (GL2JNILib.isReady){
    			GL2JNILib.HandleButtonInput(event.getDevice().getId(), event.getKeyCode(), event.getAction() == KeyEvent.ACTION_DOWN);
    		}
    		return true;
    	}
    	return super.dispatchKeyEvent(event);
    }
}
