#ifndef GRAPHICSDEBUGUNIVERSESCENE_H
#define GRAPHICSDEBUGUNIVERSESCENE_H

#include <util/mjResourceManager.h>
#include <core/mjScene.h>
#include <graphics/mj3rdPersonCamera.h>


using namespace mjEngine;

class GraphicsDebugUniverseScene: public mjScene
{
public:
    GraphicsDebugUniverseScene(mjResourceManager* resourceManager);

    // mjScene interface
public:
    void Initialize(int width, int height);
    void OnActivate() override;
    void Update(float t_elapsed) override;
    void Draw() override;
    void OnDeactivate() override;

    mjModel* DEBUGvasilisa;
    mjRenderer* debugRenderer;
    mjObject* debugVasiObject;
};

#endif // GRAPHICSDEBUGUNIVERSESCENE_H
