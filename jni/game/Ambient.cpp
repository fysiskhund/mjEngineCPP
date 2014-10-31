#include "Ambient.h"

Ambient::Ambient()
{
	//LOGI("Wind is at %p\n", &wind);
    windAutomaton.states.push_back(new SteadyDirectionState(&wind));
    //windAutomaton.states.push_back(new DustDevilState(&wind));
    windAutomaton.Start(windAutomaton.states[0]);



    for (unsigned i = 0; i < windAutomaton.states.size(); i++)
    {
       ((WindState*) windAutomaton.states[i])->stateCount = windAutomaton.states.size();
    }

    std::vector<GlowBeing*> glowBeings;
}

void Ambient::Update(float t_elapsed)
{
    windAutomaton.Update(t_elapsed);
    UpdateDustDevils(t_elapsed);

}

void Ambient::InitGlowBeings(mjCamera* camera, mjPhysics* physics, std::vector<mjShader*>* shaderList, mjSceneGraph* sceneGraph)
{
 unsigned total = 100;


    for (unsigned i = 0; i < total; i++)
    {
        GlowBeing* glowBeing = new GlowBeing(camera);


        glowBeing->TieShaders(*shaderList);

        physics->AddObject(glowBeing, 0);

        sceneGraph->translucentObjects.push_back(glowBeing);

        glowBeing->Reposition();

        glowBeings.push_back(glowBeing);
    }
}


void Ambient::CreateDustDevil(mjVector3& pos, float r, float h)
{
    std::vector<GlowBeing*>* inDustDevil = new std::vector<GlowBeing*>();
    std::vector<float>* angles = new std::vector<float>();
    std::vector<float>* rForParticle = new std::vector<float>();



    mjVector3 centerToParticle;

    for (unsigned i = 0; i < glowBeings.size(); i++)
    {
        centerToParticle.CopyFrom(pos);
        centerToParticle.Subtract(glowBeings[i]->pos);
        float normSq = centerToParticle.GetNormSquared();
        if (normSq <= r*r)
        {
            //By using +Z as a reference direction we can calculate the vector angle by comparing it to its norm
            // We discard Y because we're not interested in the vertical part of the angle, only the horizontal part
            float norm = sqrt((centerToParticle.x*centerToParticle.x) + (centerToParticle.z*centerToParticle.z));
            float angleAgainstK =  atan(centerToParticle.z/norm);
            angles->push_back(angleAgainstK);
            inDustDevil->push_back(glowBeings[i]);
            rForParticle->push_back(norm);
        }
    }
    if (inDustDevil->size() > 0)
    {
        DustDevil* dustDevil = new DustDevil();
        dustDevil->beings = inDustDevil;
        dustDevil->angles = angles;
        dustDevil->rForParticle = rForParticle;
        dustDevil->h = h;
        dustDevil->r = r;
        dustDevil->rotSpeed = 1.5;
        dustDevil->rotAccel = 0.01;
        dustDevil->vertSpeed = 0.1;
        dustDevil->rReduction = 0.01;

        dustDevils.push_back(dustDevil);
    } else
    {
        delete inDustDevil;
        delete rForParticle;
        delete angles;
    }
}

void Ambient::UpdateDustDevils(float t_elapsed)
{
    for (unsigned i = 0; i < dustDevils.size(); i++)
    {
        DustDevil* devil = dustDevils[i];

        // Take all the particles and start revolving them
        for(unsigned j = 0; j < devil->beings->size(); j++)
        {
            GlowBeing* being = (*devil->beings)[j];
            float angle = (*devil->angles)[j];
            float rForParticle = (*devil->rForParticle)[j];

            if (devil->rotSpeed < MAX_ROTSPEED)
            {
                devil->rotSpeed += devil->rotAccel*t_elapsed;
            } else
            {
                devil->phase = 1;
            }

            angle += devil->rotSpeed*t_elapsed;
            if ( angle < 0)
            {
                angle += 2.0*M_PI;
            } else if (angle > 2.0*M_PI)
            {
                angle -= 2.0*M_PI;
            }

            being->pos.x = sin(angle)*rForParticle;
            being->pos.z = cos(angle)*rForParticle;
            being->vel.y += devil->vertSpeed*t_elapsed;

            rForParticle -= devil->rReduction*t_elapsed;
            if (rForParticle > 0)
            {
                (*devil->rForParticle)[j] = rForParticle;
            }



            (*devil->angles)[j] = angle;

        }

    }
    for (int i = dustDevils.size()-1; i >= 0; i--)
    {

        if (dustDevils[i]->phase == 1)
        {

        }
    }
}
