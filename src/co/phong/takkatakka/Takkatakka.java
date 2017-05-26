/*
 * Copyright (C) 2016 Alejandro Valenzuela
 *
 */

package co.phong.takkatakka;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.util.Log;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;

import android.support.v4.view.MotionEventCompat;


import java.io.File;


public class Takkatakka extends Activity {

    GL2JNIView mView;

    @Override protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        /*try {
			Thread.sleep(3000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}*/
        
        
        mView = new GL2JNIView(getApplication());
        mView.setSystemUiVisibility( View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_FULLSCREEN
                | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
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
    public boolean onTouchEvent(MotionEvent motionEvent) {
        // MotionEvent reports input details from the touch screen
        // and other input controls. In this case, you are only
        // interested in events where the touch position changed.

    	int actionMasked = MotionEventCompat.getActionMasked(motionEvent);
		
		//System.out.println(actionToString(actionMasked));
		if (actionMasked == MotionEvent.ACTION_DOWN || 
				actionMasked == MotionEvent.ACTION_POINTER_DOWN ||
				actionMasked == MotionEvent.ACTION_UP ||
				actionMasked == MotionEvent.ACTION_POINTER_UP ||
				actionMasked == MotionEvent.ACTION_MOVE)
		{
			int pointerIndex = MotionEventCompat.getActionIndex(motionEvent);
			int touchType = 0;
			switch(actionMasked)
			{
			case MotionEvent.ACTION_POINTER_DOWN:
			case MotionEvent.ACTION_DOWN:
				touchType = 0;
				break;
			case MotionEvent.ACTION_POINTER_UP:
			case MotionEvent.ACTION_UP:
				touchType = 1;
				break;
			case MotionEvent.ACTION_MOVE:
				touchType = 2;
				break;
			}
			float x = MotionEventCompat.getX(motionEvent, pointerIndex);
			float y = MotionEventCompat.getY(motionEvent, pointerIndex);
			GL2JNILib.HandleTouchInput(pointerIndex, touchType, x, y);
			
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
