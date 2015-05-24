#ifndef GLOWBEING_H
#define GLOWBEING_H


#define GLOWBEING_TTL 4


#include <string>

#include <core/mjObject.h>
#include <physics/mjSphere.h>
#include <graphics/mjCamera.h>
#include <util/mjResourceManager.h>



using namespace mjEngine;

class GlowBeing: public mjObject
{
    public:
        float mass = 0.3;
        float ttl = GLOWBEING_TTL;
        bool canCollide = false;

        mjCamera* camera;

        GlowBeing(mjCamera* camera, mjResourceManager* resourceManager);

        const float MaxCameraDist = 4;

        void Update(float t_elapsed) override;
        void ProcessPhysicsEffects(float t_elapsed) override;
        void Reposition();

    protected:
    private:
};

#endif // GLOWBEING_H
