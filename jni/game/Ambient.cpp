#include "Ambient.h"

Ambient::Ambient()
{
	//LOGI("Wind is at %p\n", &wind);
    //windAutomaton.states.push_back(new SteadyDirectionState(&wind));
    windAutomaton.states.push_back(new DustDevilState(&wind));
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

    for (unsigned i = 0; i < glowBeings.size(); i++)
    {
        if (glowBeings[i]->pos.DistanceTo(pos) <= r)
        {
            inDustDevil.push_back(glowBeings[i]);
        }
    }
    if (inDustDevil.size() > 0)
    {
        DustDevil* dustDevil = new DustDevil();
        dustDevil->beings = inDustDevil;
        dustDevil->h = h;
        dustDevil->r = r;
        dustDevil->rotSpeed = 0.1;
        dustDevil->vertSpeed = 0.01;

        dustDevils.push_back(dustDevil);
    } else
    {
        delete inDustDevil;
    }
}

void Ambient::UpdateDustDevils(float t_elapsed)
{
    for (unsigned i = 0; i < dustDevils.size(); i++)
    {
        DustDevil* devil = dustDevils[i];

        // Take all the particles and start revolving them

    }
}
