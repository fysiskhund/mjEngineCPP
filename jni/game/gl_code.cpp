/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

// OpenGL ES 2.0 code


#include "gl_code.h"


mjSkybox* skybox;

mj3rdPersonCamera* camera;

mjDefaultShaders* defaultShaders;

float projectionMatrix[16];

float modelViewProjectionMatrix[16];
float modelViewMatrix[16];
float ratio;
bool debugMatrix = true;
float theta = 0;

Level* level;


mjPhysics* physics;


mjVector3 cameraAnglesModifier;

mjSceneGraph* sceneGraph;

Character* character;

EntityCreator entityCreator;


static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}




std::vector<mjShader*> shaderList;

void InitShaders()
{
	mjDefaultShaders* defaultShaders = new mjDefaultShaders();
	mjSkyboxShaders* skyboxShaders = new mjSkyboxShaders();

	shaderList.push_back(defaultShaders);
	shaderList.push_back(skyboxShaders);
}

void SetUpSkybox()
{
	skybox = new mjSkybox();

	mjImageLoader imgLoader;
	mjModel* skyboxBox = new mjModel();
	skyboxBox->LoadFromFile("/sdcard/mjEngineCPP/skybox.mesh.xml");

	mjModel* skyboxPlane = new mjModel();
	skyboxPlane->LoadFromFile("/sdcard/mjEngineCPP/skybox_plane.mesh.xml");

	skybox->SetModels(skyboxBox, skyboxPlane);

	skybox->LoadTexturesFromPrefix("/sdcard/mjEngineCPP/bluesky/skybox");

	char wanderingCloudName[1024];
	/*for (int i = 0; i < 3; i++)
	{
		snprintf(wanderingCloudName, 1024, "%s%d%s",  "/sdcard/mjEngineCPP/bluesky/wandering_cloud", i, ".png");
		GLuint tex0 = imgLoader.LoadToGLAndFreeMemory(wanderingCloudName);
		skybox->PushLevel(new mjSkyboxLevelData(tex0, i, 0, 0.01*i+0.02, 0));
	}*/




	skybox->SetCameraPos(&camera->pos);

	LOGI("after SetCamerapos");
}


bool setupGraphics(int w, int h) {
	PrintGLCapabilities();

	defaultShaders = new mjDefaultShaders();
	camera = new mj3rdPersonCamera();
	level = new Level();
	sceneGraph = new mjSceneGraph();
	physics = new mjPhysics();

	// Some adjustments
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	InitShaders();

    LOGI("setupGraphics(%d, %d)", w, h);




    glEnable(GL_DEPTH_TEST);



    glViewport(0, 0, w, h);
    checkGlError("glViewport");

    level->LoadFromFile("/sdcard/mjEngineCPP/levels/testlevel.xml");
    entityCreator.PopulateLevel(&level->doc, level);


    character = (Character*) level->GetEntityByID("character0");
    LOGI("character is at %p", character);







    mjImageLoader* imgLoader = new mjImageLoader();//

LOGI("Before first imgload");




    //((mjSphere*) bird.boundingStructure)->r = 0.3;

    // Test loading png texture

    LOGI("Here");




    character->gravity = &physics->gravity;

    LOGI("Here2");
    character->modelOffset.Set(0,-0.825,0);


    mjVector3 cameraOffset;
    cameraOffset.Set(0,0.7,0);
    LOGI("Here3");
    camera->SetTarget(&character->pos, cameraOffset);
    camera->r = 3;

    //charBoundStruct->SetCorners()
    //((mjSphere*) character.boundingStructure)->r = 0.5;




    float closeUpFactor = 0.5;
    ratio = closeUpFactor*((float)w)/((float)h);
    Matrix4::FrustumM(projectionMatrix, 0,
            				   -ratio, ratio, -closeUpFactor, closeUpFactor, 0.5, 50);





    LOGI("setupSkybox");
    SetUpSkybox();
    skybox->TieShaders(shaderList);


    LOGI("Adding entities");
    for (unsigned i = 0; i < level->entities.size(); i++)
    {
        physics->AddObject(level->entities[i], 0);
        sceneGraph->drawableObjects.push_back(level->entities[i]);
        level->entities[i]->TieShaders(shaderList);
    }
    LOGI("Now adding terrain");
    for (unsigned i = 0; i < level->terrain.size(); i++)
    {
        physics->AddObject(level->terrain[i], 1);
        sceneGraph->drawableObjects.push_back(level->terrain[i]);
        level->terrain[i]->TieShaders(shaderList);
    }

    LOGI("End of init");
    checkGlError("end of init");
    return true;
}





void renderFrame(float t_elapsed) {

	// Update phase
	if (character->pos.y < -5)
	{
		character->pos.Set0();
		character->pos.y = 10;
		character->vel.y = 0;
	}
	physics->Update(t_elapsed);
	camera->Update(t_elapsed);
	skybox->Update(t_elapsed);
	if (cameraAnglesModifier.GetNorm() > 0.2) {
		camera->theta += -0.02*cameraAnglesModifier.y;
		if (camera->theta > 6.283184)
			camera->theta -= 6.283184;
		else if (camera->theta < 0)
			camera->theta = 6.283184 + camera->theta;

		camera->phi += -0.02*cameraAnglesModifier.x;

		if (camera->phi > 6.283184)
			camera->phi -= 6.283184;
		else if (camera->phi < 0)
			camera->phi = 6.283184 + camera->phi;

	} else
	{
		cameraAnglesModifier.Set0();
	}
	//LOGI("camera->dir: %3.3f, %3.3f, %3.3f", camera->dir.x, camera->dir.y, camera->dir.z);
	//character.Update(0.016);


	///////// Draw start

	float lookAtMatrix[16];

    glClearColor(0.9, 0, 0.9, 1.0f);
    //checkGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    //checkGlError("glClear");



    //camera->dir.Set(0,0,-1);
    //camera->dir.Normalize();
    //camera->pos.Set(0,1.6,8);

    camera->GetLookAtMatrix(lookAtMatrix);
    skybox->Draw(shaderList, lookAtMatrix, projectionMatrix);


    //Matrix4::DebugM("lookat", lookAtMatrix);


    // Apply the transformation as defined by the pose to the modelMatrix
    //mjMatrixHelper.GetPositionScaleAndRotationMatrix(pose.positions.get(0), pose.angles.get(0), localMeshMatrix);

    /////// modelStructure operations should come here

    //mjMatrixHelper.GetPositionScaleAndRotationMatrix(pose.positions.get(currentNodeIndex), pose.angles.get(currentNodeIndex), tempMatrix);

    // Matrix multiplication should come here

    // Apply the lookAt (viewMatrix) transformation to obtain modelView transformation
    //Matrix4::MultiplyMM(modelViewMatrix, 0, viewMatrix, 0, modelMatrix, 0);

    //LOGI("%s:%d hasn't crashed yet", __FILE__, __LINE__);
    theta+= 0.01;
    if (theta >= 2.0*(3.141592))
    {
    	theta -= 2.0*(3.141592);
    }
    {
    	float x, z;
    	x = sin(theta);
    	z = cos(theta);
    	/*bird.dir.Set(z, 0, -x);
    	//character.dir.Set(x, 0, z);
    	bird.pos.Set(3.0*x,0,3.0*z);*/
    }

    //LOGI("%s:%d hasn't crashed yet", __FILE__, __LINE__);
    //character.Draw(shaderList, lookAtMatrix, projectionMatrix);
    //LOGI("%s:%d hasn't crashed yet", __FILE__, __LINE__);
    //bird.Draw(shaderList, lookAtMatrix, projectionMatrix);
    //LOGI("%s:%d hasn't crashed yet", __FILE__, __LINE__);
    //box0.Draw(shaderList, lookAtMatrix, projectionMatrix);
    //LOGI("%s:%d hasn't crashed yet", __FILE__, __LINE__);

    sceneGraph->Draw(shaderList, lookAtMatrix, projectionMatrix);

    checkGlError("afterFRame");
    //LOGI("After renderFrame");
    //character.Check();
}

void PrintGLCapabilities()
{
	printGLString("Version", GL_VERSION);
	printGLString("Vendor", GL_VENDOR);
	printGLString("Renderer", GL_RENDERER);
	printGLString("Extensions", GL_EXTENSIONS);
}

void JoystickEvent(int controllerID, int joystickID,
		float x, float y)
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
			mjMathHelper::GetForwardAndLeftDirections(camera->dir, physics->gravity, &outForwardDir, &outLeftDir);

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

				character->intrinsecVel.CopyFrom(finalForwardDir);
				character->intrinsecVel.MulScalar(2);

				if (finalForwardDir.Normalize() > 0.1)
				{
					character->dir.CopyFrom(finalForwardDir);
				}
			} else
			{
				LOGI("Strange value in finalForwardDir - %3.3f, %3.3f, %3.3f", finalForwardDir.x, finalForwardDir.y, finalForwardDir.z);
			}
			/*LOGI("initialDir %3.3f, %3.3f, %3.3f", dir.x, dir.y, dir.z);
			LOGI("cameraDir %3.3f, %3.3f, %3.3f", camera->dir.x, camera->dir.y, camera->dir.z);
			LOGI("finalforwarddir %3.3f, %3.3f, %3.3f", finalForwardDir.x, finalForwardDir.y, finalForwardDir.z);*/

		} else {
			character->intrinsecVel.Set0();
		}
	} else
	{

		cameraAnglesModifier.Set(x,y,0);




	}


	//LOGI("Controller[%d].joystick[%d]: %3.3f, %3.3f", controllerID, joystickID, x, y);
}
void JoystickButtonEvent(int controllerID, int buttonID, bool pressedDown)
{
    if (character->footing== 1)
	{
		character->jumping = 1;
	}
}

#ifdef ANDROID
extern "C" {
    JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_step(JNIEnv * env, jobject obj, jfloat t_elapsed);
    JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_HandleJoystickInput(JNIEnv * env, jobject obj, jint controllerID, jint joystickID, jfloat x, jfloat y);
    JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_HandleButtonInput(JNIEnv * env, jobject obj, jint controllerID, jint buttonID, jboolean pressedDown);
};

JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_co_phong_mjengine_GL2JNILib_step(JNIEnv * env, jobject obj, jfloat t_elapsed)
{
    renderFrame(t_elapsed);
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

