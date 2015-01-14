#ifndef DUSTDEVIL_H
#define DUSTDEVIL_H


#include <core/mjVector3.h>
#include <ai/mjAutomaton.h>
#include <ai/mjAutomatonState.h>
#include "../entities/GlowBeing.h"
#include <physics/mjCollisionTests.h>
#include <physics/mjCollisionResult.h>
#include <physics/mjPhysics.h>
#include <graphics/mjShader.h>
#include <graphics/mjSceneGraph.h>
#include <graphics/mjCamera.h>


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
        std::vector<float>* rsForParticle;
        DustDevil(float r, float h, std::vector<GlowBeing*>* beings, std::vector<float>* angles, std::vector<float>* rForParticle);
        void Update(float t_elapsed);
        ~DustDevil();
};

#endif // DUSTDEVIL_H
