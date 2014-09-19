#include "mjSkybox.h"

namespace mjEngine {


mjSkybox::mjSkybox()
{
	scale.Set(10,10,10);
}

void mjSkybox::PushLevel(GLuint texture)
{
	levels.push_back(texture);
}
void mjSkybox::SetModels(mjModel* boxModel, mjModel* planeModel)
{
	this->boxModel = boxModel;
	this->planeModel = planeModel;
}

void mjSkybox::LoadTexturesFromPrefix(const char* prefix)
{
	char* pathName = new char[1024];
	const char* extension = ".png"; //FIXME: enable change to jpg when jpg library is added
	mjImageLoader imgLoader;


	for (int i = 0; i< 6; i++)
	{


		// Find last "_"
		int suffixIndex = 0;

		char* name = boxModel->meshes[i]->name;


		//LOGI("name: %s", name);
		for (int j = 0; j < strnlen(name, 1024)-1; j++)
		{
			if (name[j] == '_')
			{
				suffixIndex = j;
			}
		}
		char* suffix = &name[suffixIndex];

		//LOGI("Suffix: %s", suffix);

		snprintf(pathName, 1024, "%s%s%s", prefix, suffix, extension);

		boxModel->meshes[i]->glTexture =  imgLoader.LoadToGLAndFreeMemory(pathName, GL_CLAMP_TO_EDGE);
		//LOGI("loading %s -> texture%d", pathName, boxModel->meshes[i]->glTexture);
	}



	delete[] pathName;
}

void mjSkybox::TieShaders(std::vector<mjShader*>& shaderList)
{
	int skyboxShaderIndex = 0;
	for (int j = 0; j < shaderList.size(); j++)
	{
		//LOGI("Considering shader %s", shaderList[j]->name);
		if (strncmp("skybox", shaderList[j]->name, 96) == 0)
		{
			skyboxShaderIndex = j;
		}
	}
	for(int i = 0; i < boxModel->meshes.size(); i++)
	{
		boxModel->meshes[i]->mjShaderListIndex = skyboxShaderIndex;
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
}
void mjSkybox::Draw(std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix)
{
	//LOGI("draw skybox");
	// turn off depth buffer
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	model = boxModel;
	mjObject::Draw(shaderList, lookAtMatrix, projectionMatrix);

	/*
	model = planeModel;
	for(int i = 0; i < levels.size(); i++)
	{
		mjObject::Draw(shaderList, lookAtMatrix, projectionMatrix);
	}*/


	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
}
}
