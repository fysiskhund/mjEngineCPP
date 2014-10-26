#ifndef GLOWBEING_H
#define GLOWBEING_H


#define GLOWBEING_TTL 4

#include "../core/mjObject.h"
#include "../graphics/mjImageLoader.h"
#include "../graphics/mjCamera.h"


using namespace mjEngine;

class GlowBeing: public mjObject
{
    public:
        float mass = 0.01;
        float ttl = GLOWBEING_TTL;
        bool canCollide = false;

        mjCamera* camera;

        GlowBeing(mjCamera* camera);

        const float MaxCameraDist = 64;

        void Update(float t_elapsed) override;
        void ProcessPhysicsEffects(float t_elapsed) override;
        void Reposition();

    protected:
    private:
};

#endif // GLOWBEING_H
