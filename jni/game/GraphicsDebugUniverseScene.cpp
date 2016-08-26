#include "GraphicsDebugUniverseScene.h"

GraphicsDebugUniverseScene::GraphicsDebugUniverseScene(mjResourceManager* resourceManager)
    :mjScene(resourceManager)
{

}

void GraphicsDebugUniverseScene::Initialize(int width, int height)
{
    camera = new mj3rdPersonCamera();
    glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK); //FIXME: just testing
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.6f, 0.6f, 0.9f, 1.0f);


    glEnable(GL_DEPTH_TEST);
    checkGlError("depthtest");


    glViewport(0, 0, width, height);
    checkGlError("glViewport");

    float closeUpFactor = 0.5;
    float ratio = closeUpFactor*((float)width)/((float)height);

    Matrix4::FrustumM(projectionMatrix, 0,
                               -ratio, ratio, -closeUpFactor, closeUpFactor, 0.5, 70);

    DEBUGvasilisa = resourceManager->FetchModel("bird.mesh.xml");
    checkGlError("fetch Model");
    debugRenderer = new mjRenderer();
    checkGlError("createRenderer");
    debugRenderer->PrepareForModel(*DEBUGvasilisa);
    debugVasiObject = new mjObject();


    GLuint glTexture = resourceManager->FetchTexture("birdtexture.png", GL_CLAMP_TO_EDGE);
    for (unsigned i = 0; i < DEBUGvasilisa->meshes.size(); i++)
    {
        DEBUGvasilisa->meshes[i]->glTexture = glTexture;
    }
    LOGI("End of init");


}




void GraphicsDebugUniverseScene::OnActivate()
{
}

void GraphicsDebugUniverseScene::Update(float t_elapsed)
{
}

void GraphicsDebugUniverseScene::Draw()
{
    float modelMatrix[16];

    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


    camera->pos.Set(0, 0, 5);

    camera->GetLookAtMatrix(lookAtMatrix);

    debugVasiObject->CopyModelMatrixTo(modelMatrix);

    debugRenderer->RenderModel(*DEBUGvasilisa, modelMatrix, lookAtMatrix, projectionMatrix, NULL, NULL);

}

void GraphicsDebugUniverseScene::OnDeactivate()
{
}
