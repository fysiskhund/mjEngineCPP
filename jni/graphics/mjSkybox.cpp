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
        this->customShaders = new std::vector<mjShader*>();
        mjShader* skyboxShader = resourceManager->FetchShader("skybox")->shader;
        this->customShaders->push_back(skyboxShader);

		//LOGI("loading %s -> texture%d", pathName, boxModel->meshes[i]->glTexture);
	}



	delete[] pathName;
}



void mjSkybox::SetCameraPos(mjVector3* cameraPos)
{
	this->cameraPos = cameraPos;

}
void mjSkybox::Update(double t_elapsed)
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

}
