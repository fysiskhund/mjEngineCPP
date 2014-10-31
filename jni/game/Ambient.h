#ifndef AMBIENT_H
#define AMBIENT_H

#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>


#include "../core/mjVector3.h"
#include "../ai/mjAutomaton.h"
#include "../ai/mjAutomatonState.h"
#include "windStates/SteadyDirectionState.h"
#include "windStates/DustDevilState.h"
#include "../entities/GlowBeing.h"
#include "../physics/mjCollisionTests.h"
#include "../physics/mjCollisionResult.h"
#include "../physics/mjPhysics.h"
#include "../graphics/mjShader.h"
#include "../graphics/mjSceneGraph.h"
#include "../graphics/mjCamera.h"


using namespace mjEngine;


#define MAX_ROTSPEED 20

class DustDevil
{
    public:
        mjVector3 pos;
        float r;
        float h;

        int phase = 0;
        float rotSpeed;
        float vertSpeed;
        float rotAccel;
        float rReduction;
        std::vector<GlowBeing*>* beings;
        std::vector<float>* angles;
        std::vector<float>* rForParticle;
};

class Ambient
{
    public:

        mjVector3 wind;
        std::vector<GlowBeing*> glowBeings;
        std::vector<DustDevil*> dustDevils;


        Ambient();

        void Update(float t_elapsed);

        void InitGlowBeings(mjCamera* camera, mjPhysics* physics, std::vector<mjShader*>* shaderList, mjSceneGraph* sceneGraph);

        void CreateDustDevil(mjVector3& pos, float r, float h);



        mjAutomaton windAutomaton;
    protected:
        void UpdateDustDevils(float t_elapsed);
    private:

};

#endif // AMBIENT_H
