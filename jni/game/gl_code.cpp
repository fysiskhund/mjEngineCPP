/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

// OpenGL ES 2.0 code


#include "gl_code.h"

// For now since the renderer doesn't hold states (or anything), this can be done without problem.
#if defined(USE_GL3) || defined(USE_GLES2)
mjRendererGL renderer;
#else
mjRenderer renderer;
#endif

PlatformUniverseScene* platformUniverse;
GraphicsDebugUniverseScene* graphicsDebugUniverse;
mjSceneManager sceneManager;

mjResourceManager* resourceManager;

bool setupGame(int w, int h, std::string& pathPrefix) {
    LOGI("Screen resolution: %d x %d", w, h);
    resourceManager = new mjResourceManager(pathPrefix, &renderer);
    /*graphicsDebugUniverse = new GraphicsDebugUniverseScene(resourceManager);
    graphicsDebugUniverse->Initialize(w,h);
    sceneManager.SetFirstScene(graphicsDebugUniverse);*/

    platformUniverse = new PlatformUniverseScene(resourceManager);
    LOGI("%s %d: new %s", __FILE__, __LINE__, "platformUniverse");

    platformUniverse->Initialise(w,h);
    sceneManager.SetFirstScene(platformUniverse);
    return true;
}

void renderFrame(float t_elapsed) {
	sceneManager.Update(t_elapsed);


}
void PrintGLCapabilities()
{
/*	printGLString("Version", GL_VERSION);
	printGLString("Vendor", GL_VENDOR);
	printGLString("Renderer", GL_RENDERER);
	printGLString("Extensions", GL_EXTENSIONS);*/
}

void JoystickEvent(int controllerID, int joystickID,
		float x, float y)
{

    if (!platformUniverse->character->ignoreInput)
    {
        if (joystickID == 0)
        {
            mjVector3 dir;
            dir.Set(x,0,y);

            float norm = dir.GetNorm();
            if (norm > 0.2)
            {
                mjVector3 outForwardDir;
                mjVector3 outLeftDir;

                //invGravity.Normalize();
                mjMathHelper::GetForwardAndLeftDirections(platformUniverse->camera->dir,
                                                          platformUniverse->physics.gravity,
                                                          &outForwardDir, &outLeftDir);

                mjVector3 finalForwardDir;
                // The joystick directions need to be inverted because technically they are:
                // in the Y axis, the joystick going "up" outputs a negative y value and viceversa.
                // In the X axis, pushing the joystick towards the left results in a negative value.
                // conceptually it needs to be inverted.
                //

                finalForwardDir.ScaleAdd(-y, outForwardDir);
                finalForwardDir.ScaleAdd(-x, outLeftDir);

                float finalForwardDirNorm = finalForwardDir.GetNorm();

                if (finalForwardDirNorm > 0.01 && finalForwardDirNorm < 4)
                {

                    platformUniverse->character->intrinsecVel.CopyFrom(finalForwardDir);
                    platformUniverse->character->intrinsecVel.MulScalar(2);

                    if (finalForwardDir.Normalize() > 0.1)
                    {
                        platformUniverse->character->dir.CopyFrom(finalForwardDir);
                    }
                } else
                {
                    LOGI("Strange value in finalForwardDir - %3.3f, %3.3f, %3.3f", finalForwardDir.x, finalForwardDir.y, finalForwardDir.z);
                }
                /*LOGI("initialDir %3.3f, %3.3f, %3.3f", dir.x, dir.y, dir.z);
            LOGI("cameraDir %3.3f, %3.3f, %3.3f", camera->dir.x, camera->dir.y, camera->dir.z);
            LOGI("finalforwarddir %3.3f, %3.3f, %3.3f", finalForwardDir.x, finalForwardDir.y, finalForwardDir.z);*/

            } else {
                platformUniverse->character->intrinsecVel.Set0();
            }
        } else
        {

            platformUniverse->cameraAnglesModifier.Set(x,y,0);




        }

    }
	//LOGI("Controller[%d].joystick[%d]: %3.3f, %3.3f", controllerID, joystickID, x, y);
}
void JoystickButtonEvent(int controllerID, int buttonID, bool pressedDown)
{
    if (pressedDown)
    {
        if (platformUniverse->character->hasFooting== 1 && (platformUniverse->character->jumping == -1))
        {
            platformUniverse->character->jumping = 1;
        }
    } else
    {
        platformUniverse->character->jumping = -1;
    }
}

void TouchEvent(int fingerID, int x, int y, bool pressedDown)
{
    mjInputEvent event;
    
    event.fingerID = fingerID;
    event.x = x;
    event.y = y;
    
    event.type = pressedDown? MJ_FINGERDOWN : MJ_FINGERUP;
    
    
    sceneManager.currentScene->OnInput(event);

}

#ifdef ANDROID
extern "C" {
    JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height, jstring jPathPrefix);
    JNIEXPORT jboolean JNICALL Java_co_phong_mjengine_GL2JNILib_step(JNIEnv * env, jobject obj, jfloat t_elapsed);

    JNIEXPORT jbyteArray JNICALL Java_co_phong_mjengine_GL2JNILib_HandleEngineQuery(JNIEnv * env);
    JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_HandleJoystickInput(JNIEnv * env, jobject obj, jint controllerID, jint joystickID, jfloat x, jfloat y);
    JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_HandleButtonInput(JNIEnv * env, jobject obj, jint controllerID, jint buttonID, jboolean pressedDown);

};

JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height, jstring jPathPrefix)
{
	const char* jPathPrefixChars = env->GetStringUTFChars(jPathPrefix, 0);

	std::string pathPrefix = jPathPrefixChars;
	LOGI("Platform path is %s", pathPrefix.c_str());
    setupGame(width, height, pathPrefix);
}

JNIEXPORT jboolean JNICALL Java_co_phong_mjengine_GL2JNILib_step(JNIEnv * env, jobject obj, jfloat t_elapsed)
{
    renderFrame(t_elapsed);
    return mjMultiPlatform::commandsForJNIPresent;

}


JNIEXPORT jbyteArray JNICALL Java_co_phong_mjengine_GL2JNILib_HandleEngineQuery(JNIEnv * env)
{
	LOGI("Sending command %s", mjMultiPlatform::commandsForJNI.c_str());
    int byteCount = mjMultiPlatform::commandsForJNI.length();
    jbyte* pNativeMessage = (jbyte*)mjMultiPlatform::commandsForJNI.c_str();
    jbyteArray bytes = env->NewByteArray(byteCount);
    env->SetByteArrayRegion(bytes, 0, byteCount, pNativeMessage);

    mjMultiPlatform::commandsForJNIPresent = false; // turn off flag.
    return bytes;
}

JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_SendEngineQuery(JNIEnv * env, jstring cmdStr)
{
	//char* cmdCChar;
	//cmdCChar = env->GetStringUTFChars(env, cmdStr, NULL);

}

JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_HandleJoystickInput(JNIEnv * env, jobject obj, jint controllerID, jint joystickID,
		jfloat x, jfloat y)
{
    JoystickEvent(controllerID, joystickID,
		x, y);

}

JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_HandleButtonInput(JNIEnv * env, jobject obj, jint controllerID, jint buttonID, jboolean pressedDown)
{
	JoystickButtonEvent(controllerID, buttonID, pressedDown);
}
#endif

