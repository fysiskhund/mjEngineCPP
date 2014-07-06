/*
Copyright (c) 2014, Alejandro Valenzuela Roca
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
package co.phong.mjengine;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;






public class mjRenderer implements GLSurfaceView.Renderer {

	
	//public mjScene currentScene;
	Context context;
	double thisFrameTime;
	double previousFrameTime;
	float maximumTimeStep = 0.017f;
	boolean useOrtho = false;
	float ratio;
	

////////
	public mjRenderer()
	{
		super();
	}
	public mjRenderer(boolean useOrtho)
	{
		super();
		this.useOrtho = useOrtho;
		
	}
	

	public void onDrawFrame(GL10 gl) {
		thisFrameTime = android.os.SystemClock.elapsedRealtime();
		float t_elapsed = (float)((thisFrameTime - previousFrameTime)*0.001d);
		
		if (t_elapsed > 0 && t_elapsed < 1)
		{			
			float remaining_t = t_elapsed;
			float partial_t; 
			while (remaining_t > 0)
			{
				
				if (remaining_t > maximumTimeStep)
				{
					partial_t = maximumTimeStep;
				} else
				{
					partial_t = remaining_t;
				}
				//mjSceneManager.currentScene.OnUpdate(partial_t);
				remaining_t -= partial_t;
			}
			
		} else {
			System.out.println("mjRenderer - strange t_elapsed:" + t_elapsed);
		}
		
		//mjSceneManager.currentScene.OnDraw(t_elapsed, StereoProjection.Center);
		
		//mjSceneManager.ProcessSwitchToScene();
        previousFrameTime = thisFrameTime;
	}
	public void UseOrtho(boolean useOrtho)
	{
	    // this projection matrix is applied to object coordinates
	    // in the onDrawFrame() method
	    this.useOrtho = useOrtho;
	    if (useOrtho)
	    {
	    	/*Matrix.orthoM(mjGL2Helper.projectionMatrix, 0, 
	    			-ratio, ratio, 1, 1, 1, 100);
	    } else {
		    Matrix.frustumM(mjGL2Helper.projectionMatrix, 0, 
		    		-ratio, ratio, -1, 1, 1, 100);*/
	    }
	}
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		GLES20.glViewport(0, 0, width, height);

	    ratio = (float) width / height;
	    //mjGame.viewportWidth = width;
	    //mjGame.viewportHeight = height;

	    // this projection matrix is applied to object coordinates
	    // in the onDrawFrame() method
	    
	    if (useOrtho)
	    {
	    	/*Matrix.orthoM(mjGL2Helper.projectionMatrix, 0, 
	    			-ratio, ratio, -1, 1, 1, 100);

	    } else {
		    Matrix.frustumM(mjGL2Helper.projectionMatrix, 0, 
		    		-ratio, ratio, -1, 1, 1, 100);*/
	    }
	}

	public void SetupGL(){
		
	}
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
	
        
	// Background colour is almost black with a touch of blue
        
	 GLES20.glClearColor(0.01f, 0.01f, 0.4f, 1.0f);
		
     // Init texturing
     GLES20.glEnable(GLES20.GL_TEXTURE_2D);
     GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR); 
     GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR); 
     // Turn alpha blending on
     GLES20.glEnable(GLES20.GL_BLEND);
     GLES20.glBlendFunc(GLES20.GL_SRC_ALPHA, GLES20.GL_ONE_MINUS_SRC_ALPHA);
     GLES20.glEnable(GLES20.GL_DEPTH_TEST);
     GLES20.glEnable(GLES20.GL_CULL_FACE);
    //GLES20.glCullFace(GLES20.GL_CCW);
          
     //mjGL2Helper.Init(context);
     //mjSceneManager.currentScene.OnEnter(context);
     
       
     
	}
	
	public void Init(Context activityContext)
	{
		this.context = activityContext;
		//mjSceneManager.currentScene = startScene;
		//mjSceneManager.nextScene = startScene;
		
		
		
	}
    
}
