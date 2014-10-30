#include "DustDevilState.h"

DustDevilState::DustDevilState(mjVector3* wind)
:WindState(wind)
{
	this->wind = wind;
}

void DustDevilState::Enter()
{
    WindState::Enter();

    theta = ((float)rand()/(float)RAND_MAX)*2.0*3.141592;
    hDirection = ((float)rand()/(float)RAND_MAX)*2;
    if (hDirection == 0)
    {
        hDirection = -1;
    }

    intensity = 0.11;//((float)rand()/(float)RAND_MAX)*0.03;
    //LOGI("Dust devil intensity %f hdir %d\n", intensity, hDirection);
}

void DustDevilState::Execute(float t_elapsed)
{
    theta += (hDirection*t_elapsed*5.0);

    if (theta > (2.0*3.141592))
    {
        theta -= 2.0*3.141592;
    } else if (theta < 0)
    {
        theta += 2.0*3.141592;
    }

    wind->x = 2.0*cos(theta);
    wind->z = 2.0*sin(theta);
    wind->y = (float) 0.01;

     LOGI("wind: %3.3f, %3.3f, %3.3f\n", wind->x, wind->y, wind->z);
    //wind->y = (((float)rand()/(float)RAND_MAX) - 0.3)*0.5;

}
