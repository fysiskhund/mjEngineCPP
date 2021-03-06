#ifndef GLOWBEING_H
#define GLOWBEING_H


#define GLOWBEING_TTL 4


#include <string>

#include <core/mjObject.h>
#include <physics/mjSphere.h>
#include <graphics/mjCamera.h>
#include <util/mjResourceManager.h>
#include "KosmoObject.h"



using namespace mjEngine;

class GlowBeing: public KosmoObject
{
    public:
        float mass = 0.3;
        float ttl = GLOWBEING_TTL;
        bool canCollide = false;

        mjCamera* camera;

        GlowBeing(Level* levelData, mjCamera* camera, mjResourceManager* resourceManager);

        const float MaxCameraDist = 4;

        void Update(double t_elapsed) override;
        void ProcessPhysicsEffects(double t_elapsed) override;
        void Reposition();

    protected:
    private:
};

#endif // GLOWBEING_H
