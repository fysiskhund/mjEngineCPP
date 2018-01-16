#include "DustDevil.h"

DustDevil::DustDevil(float r, float h, std::vector<GlowBeing*>* beings, std::vector<float>* angles, std::vector<float>* rForParticle)
{
    this->r = r;
    this->h = h;
    this->beings = beings;
    this->angles = angles;
    this->rsForParticle = rForParticle;
    //ctor
}

void DustDevil::Update(double t_elapsed)
{
// Take all the particles and start revolving them
        for(unsigned j = 0; j < beings->size(); j++)
        {
            GlowBeing* being = (*beings)[j];
            float angle = (*angles)[j];
            float rForParticle = (*rsForParticle)[j];

            if (rotSpeed < MAX_ROTSPEED)
            {
                rotSpeed += rotAccel*t_elapsed;
            } else
            {
                phase = 1;
                LOGI("Max rotspeed reached.\n");
            }

            angle += rotSpeed*t_elapsed;
            if ( angle < 0)
            {
                angle += 2.0*M_PI;
            } else if (angle > 2.0*M_PI)
            {
                angle -= 2.0*M_PI;
            }

            being->pos.x = sin(angle)*rForParticle;
            being->pos.z = cos(angle)*rForParticle;
            being->vel.y += vertSpeed*t_elapsed;

            rForParticle -= rReduction*t_elapsed;
            if (rForParticle > 0)
            {
                (*rsForParticle)[j] = rForParticle;
            }



            (*angles)[j] = angle;

        }
}

DustDevil::~DustDevil()
{
    for (unsigned i = 0; i < beings->size(); i++)
    {
        GlowBeing* being = (*beings)[i];
        // Apply the tangential speed to all the beings, to make the transition much smoother.
        float angle = (*angles)[i];
        float rForParticle = (*rsForParticle)[i];

        being->vel.x = sin(angle);
        being->vel.z = cos(angle);
    }
    delete beings;
    delete angles;
    delete rsForParticle;

}
