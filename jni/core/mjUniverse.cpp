#include "mjUniverse.h"

namespace mjEngine
{

mjUniverse::mjUniverse(mjResourceManager* resourceManager)
{
    this->resourceManager = resourceManager;
}

void mjUniverse::OnActivate(mjGameState* currentGameState)
{
    universeState = MJ_UNIVERSE_ACTIVATED;
}


void mjUniverse::Update(double t_elapsed)
{
    physics.Update(t_elapsed);
    sceneGraph.Update(t_elapsed);
}

void mjUniverse::OnInput(mjInputEvent& event)
{

}

void mjUniverse::Draw(bool clearFrameBuffer)
{
    if (clearFrameBuffer)
    {
        glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    }
    camera->GetLookAtMatrix(lookAtMatrix);
    sceneGraph.Draw(camera, shaderList, lookAtMatrix, projectionMatrix);
}

void mjUniverse::OnDeactivate()
{
    universeState = MJ_UNIVERSE_DEACTIVATED;
}

void mjUniverse::SetName(const char* thisUniverseName)
{
    universeName = new char[strnlen(thisUniverseName, 128)+1];
    LOGI("%s %d: new %s", __FILE__, __LINE__, "char (scene's name)");
    strncpy(universeName, thisUniverseName, strnlen(thisUniverseName, 127)+1); // Copy the string terminator too
}

void mjUniverse::SetNextUniverse(const char* name)
{
    if (nextUniverseByName)
    {
        delete [] nextUniverseByName;
    }
    nextUniverseByName = new char[strnlen(name, 128)+1];
    LOGI("%s %d: new %s", __FILE__, __LINE__, "char (scene by name)");
    strncpy(nextUniverseByName, name, strnlen(name, 127)+1); // Copy the string terminator too
}

void mjUniverse::SetTransition(const char* name)
{
    if (transitionByName)
    {
        delete [] transitionByName;
    }
    transitionByName = new char[strnlen(name, 128)+1];
    LOGI("%s %d: new %s", __FILE__, __LINE__, "char (transition by name)");
    strncpy(transitionByName, name, strnlen(name, 127)+1); // Copy the string terminator too
}

mjUniverse::~mjUniverse()
{
    //dtor
}
}
