#include "mjSkybox.h"

namespace mjEngine {


mjSkybox::mjSkybox(mjResourceManager* resourceManager)
    : mjObject(resourceManager)
{
	scale.Set(10,10,10);
	backgroundData.deltaH = 0.005;
    this->resourceManager = resourceManager;
	//level0Data.deltaH = 0.01;
}

void mjSkybox::PushLevel(mjSkyboxLevelData* data)
{
	//LOGI("pushdata: 0x%x", data);
	levels.push_back(data);
	//planeModel->meshes.at(0)->glTexture = data->texture;
}
void mjSkybox::SetModels(mjModel* boxModel, mjModel* planeModel)
{
	this->boxModel = boxModel;
	this->planeModel = planeModel;
    this->model = boxModel;
}

void mjSkybox::LoadTexturesFromPrefix(const char* prefix)
{
	char* pathName = new char[1024];
    LOGI("%s %d: new %s", __FILE__, __LINE__, "char[] for path");
	const char* extension = ".png"; //FIXME: enable change to jpg when jpg library is added
	mjImageLoader imgLoader;


	for (int i = 0; i< 6; i++)
	{


		// Find last "_"
		int suffixIndex = 0;

		char* name = boxModel->meshes[i]->name;



		//LOGI("name: %s", name);
		//Find the last "_", use it as suffix marker.
		for (unsigned j = 0; j < strnlen(name, 1024)-1; j++)
		{
			if (name[j] == '_')
			{
				suffixIndex = j;
			}
		}
		char* suffix = &name[suffixIndex];

		//LOGI("Suffix: %s", suffix);

		snprintf(pathName, 1024, "%s%s%s", prefix, suffix, extension);

		boxModel->meshes[i]->glTexture =  resourceManager->FetchTexture(pathName, GL_CLAMP_TO_EDGE);//imgLoader.LoadToGLAndFreeMemory(pathName, GL_CLAMP_TO_EDGE);
        char* shaderName = new char[7];
        LOGI("%s %d: new %s", __FILE__, __LINE__, "char for shaderName");
        snprintf(shaderName, 7, "%s", "skybox");
        boxModel->meshes[i]->shaderName = shaderName;

		//LOGI("loading %s -> texture%d", pathName, boxModel->meshes[i]->glTexture);
	}



	delete[] pathName;
}

void mjSkybox::TieShadersDEPRECATED(std::vector<mjShader*>& shaderList)
{
	int skyboxShaderIndex = 0;
	for (unsigned j = 0; j < shaderList.size(); j++)
	{
		//LOGI("Considering shader %s", shaderList[j]->name);
		if (strncmp("skybox", shaderList[j]->name, 96) == 0)
		{
			skyboxShaderIndex = j;
		}
	}
	for(unsigned i = 0; i < boxModel->meshes.size(); i++)
	{
		boxModel->meshes[i]->mjShaderListIndex = skyboxShaderIndex;
	}
	for(unsigned i = 0; i < planeModel->meshes.size(); i++)
	{
		//LOGI("Planemodel 0x%x mesh 0x%x -> skybox shader", planeModel, planeModel->meshes[i]);
		planeModel->meshes[i]->mjShaderListIndex = skyboxShaderIndex;
	}
}

void mjSkybox::SetCameraPos(mjVector3* cameraPos)
{
	this->cameraPos = cameraPos;

}
void mjSkybox::Update(float t_elapsed)
{
	if (cameraPos)
	{
		pos.CopyFrom(*cameraPos);
	}
	backgroundData.Update(t_elapsed);



	for(unsigned i = 0; i < levels.size(); i++)
	{
		levels.at(i)->Update(t_elapsed);
	}
	//LOGI("angles: %3.3f, %3.3f -> %3.3f %3.3f %3.3f", level0Data.angleH, level0Data.angleV, dir.x, dir.y, dir.z);
}
void mjSkybox::DrawDEPRECATED(std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix, mjMatrixStack* matrixStack)
{
	//LOGI("draw skybox");
	// turn off depth buffer
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	model = boxModel;

	dir.SetRotations(backgroundData.angleH, backgroundData.angleV);
    //FIXME!!
    //mjObject::Draw(shaderList, lookAtMatrix, projectionMatrix, matrixStack);

	model = planeModel;
	//LOGI("planeModel 0x%x, mesh 0x%x", model, model->meshes.at(0));
	for(unsigned i = 0; i < levels.size(); i++)
	{
		mjSkyboxLevelData* data = levels.at(i);
		//LOGI("data: 0x%x, tex: %d", data, data->texture);
		//LOGI("modelMesh 0x%x", model->meshes.at(0));
		model->meshes.at(0)->glTexture = data->texture;
		dir.SetRotations(data->angleH, data->angleV);
        //FIXME!!
        //mjObject::Draw(shaderList, lookAtMatrix, projectionMatrix, matrixStack);
	}


	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
}
}
