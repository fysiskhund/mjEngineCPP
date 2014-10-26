#include "GlowBeing.h"


GlowBeing::GlowBeing(mjCamera* camera)
{
    this->camera = camera;
    model = new mjModel();
	model->LoadFromFile("/sdcard/mjEngineCPP/sprite.mesh.xml");



	mjImageLoader imgLoader;
	GLuint glTexture = imgLoader.LoadToGLAndFreeMemory("/sdcard/mjEngineCPP/glowbeing.png");
	for (unsigned i = 0; i < model->meshes.size(); i++)
	{
		model->meshes[i]->glTexture = glTexture;

		if (model->meshes[i]->shaderName)
            delete [] model->meshes[i]->shaderName;

		model->meshes[i]->shaderName = new char[7];
        strncpy(model->meshes[i]->shaderName, "skybox", strnlen("skybox", 10)+1);
	}

	scale.Set(0.3, 0.3, 0.3);
}

void GlowBeing::Update(float t_elapsed)
{
    mjObject::Update(t_elapsed);

    //float velNorm = vel.GetNorm();

    //vel.y += velNorm*0.005;

    if (pos.DistanceSquaredTo(camera->pos) > MaxCameraDist)
    {
        Reposition();
    }

    //Orient to the camera's directions
    dir.CopyFrom(camera->dir);
    dir.MulScalar(-1);
    up.CopyFrom(camera->up);

}

void GlowBeing::Reposition()
{
    pos.CopyFrom(camera->pos);
    pos.x += -10.0 + ((float)rand()/(float)RAND_MAX) * 20.0;
    pos.y += -10.0 + ((float)rand()/(float)RAND_MAX) * 20.0;
    pos.z += -10.0 + ((float)rand()/(float)RAND_MAX) * 20.0;
    vel.Set0();
}

void GlowBeing::ProcessPhysicsEffects(float t_elapsed)
{
	accel.Set0();

	for (unsigned i = 0; i < effectStack.size(); i++)
	{
		switch(effectStack[i]->type)
		{

            case MJ_GRAVITY: // Gravity is reduced to simulate floating on air
				accel.ScaleAdd(0.1, effectStack[i]->value);
			case MJ_ACCELERATION:


			break;
			case MJ_FORCE:
                accel.ScaleAdd(1.0/mass, effectStack[i]->value);
			break;
			default:
				break;
		}

		//if (effectStack[i]->)
	}
	effectStack.clear();

	if (!boundingStructure->isImmovable)
	{

		vel.ScaleAdd(t_elapsed, accel);

	}
}
