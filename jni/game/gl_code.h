#ifndef GL_CODE_H
#define GL_CODE_H

#ifdef ANDROID
#include <jni.h>
#endif




#include <extLibs/logger/mjLog.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>


#include <graphics/mjModel.h>
#include <core/mjSceneManager.h>
#include <core/mjObject.h>
#include <graphics/mjImageLoader.h>
#include <graphics/mjDefaultShaders.h>
#include <graphics/mjSkyboxShaders.h>
#include <core/mjVector3.h>

#include <extLibs/math/Matrix.h>
#include <graphics/mj3rdPersonCamera.h>
#include <graphics/mjSkybox.h>
#include <physics/mjPhysics.h>
#include <graphics/mjSceneGraph.h>
#include <extLibs/util/mjMultiPlatform.h>
#include "entities/Character.h"
#include "Level.h"
#include "EntityCreator.h"

using namespace mjEngine;



#include "PlatformUniverseScene.h"

//static void printGLString(const char *name, GLenum s);

//static void checkGlError(const char* op);


bool setupGame(int w, int h, mjResourceManager* resourceManager);

void renderFrame(float t_elapsed);

void PrintGLCapabilities();

void JoystickEvent(int controllerID, int joystickID,
		float x, float y);

void JoystickButtonEvent(int controllerID, int buttonID, bool pressedDown);

#endif
