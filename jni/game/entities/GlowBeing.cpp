#include "GlowBeing.h"


GlowBeing::GlowBeing(Level* levelData, mjCamera* camera, mjResourceManager* resourceManager)
: KosmoObject(resourceManager, levelData)
{
    this->camera = camera;

    model = resourceManager->FetchModel("entities/sprite.mesh.xml");



    GLuint glTexture = resourceManager->FetchTexture("entities/glowbeing.png", GL_CLAMP_TO_EDGE);

	for (unsigned i = 0; i < model->meshes.size(); i++)
	{
		model->meshes[i]->glTexture = glTexture;

		if (model->meshes[i]->shaderName)
            delete [] model->meshes[i]->shaderName;

		model->meshes[i]->shaderName = new char[7];
        LOGI("%s %d: new %s", __FILE__, __LINE__, "char [] for shaderName");

        strncpy(model->meshes[i]->shaderName, "skybox", strnlen("skybox", 10)+1);
	}

	scale.Set(0.3, 0.3, 0.3);

    mjSphere* boundingStruct = ((mjSphere*)boundingStructure);
    boundingStruct->r = 0;

}

void GlowBeing::Update(double t_elapsed)
{
    mjObject::Update(t_elapsed);

    //float velNorm = vel.GetNorm();

    //vel.y += velNorm*0.005;

    if (pos.DistanceSquaredTo(camera->pos) > MaxCameraDist*MaxCameraDist)
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
    pos.x += -MaxCameraDist +( ((float)rand()/(float)RAND_MAX) * 2.0*MaxCameraDist);
    pos.y += -MaxCameraDist +( ((float)rand()/(float)RAND_MAX) * 2.0*MaxCameraDist);
    pos.z += -MaxCameraDist +( ((float)rand()/(float)RAND_MAX) * 2.0*MaxCameraDist);
    vel.Set0();
}

void GlowBeing::ProcessPhysicsEffects(double t_elapsed)
{
	accel.Set0();

	for (unsigned i = 0; i < effectStack.size(); i++)
	{
		switch(effectStack[i]->type)
		{

            case MJ_GRAVITY: // Gravity is reduced to simulate floating on air
				//accel.ScaleAdd(0.001, effectStack[i]->value);
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

	if (!boundingStructure->isImmovable)
	{

		vel.ScaleAdd(t_elapsed, accel);

	}
}
