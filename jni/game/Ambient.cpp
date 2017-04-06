#include "Ambient.h"

Ambient::Ambient()
{
	//LOGI("Wind is at %p\n", &wind);
    windAutomaton.states.push_back(new SteadyDirectionState(&wind));
    LOGI("%s %d: new %s", __FILE__, __LINE__, "new wind");
    //windAutomaton.states.push_back(new DustDevilState(&wind));
    windAutomaton.SetStartState(windAutomaton.states[0]);



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

void Ambient::InitGlowBeings(Level* levelData, mjCamera* camera, mjPhysics* physics, std::vector<mjShader*>* shaderList, mjSceneGraph* sceneGraph, mjResourceManager& resourceManager)
{
 unsigned total = 100;


    for (unsigned i = 0; i < total; i++)
    {
        GlowBeing* glowBeing = new GlowBeing(levelData, camera, &resourceManager);
        LOGI("%s %d: new %s", __FILE__, __LINE__, "glowbeing");


        //glowBeing->TieShaders(*shaderList);

        physics->AddObject(glowBeing, 0);

        //sceneGraph->translucentObjects.push_back(glowBeing);

        glowBeing->Reposition();

        glowBeings.push_back(glowBeing);
    }
}


void Ambient::CreateDustDevil(mjVector3& pos, float r, float h)
{
    std::vector<GlowBeing*>* inDustDevil = new std::vector<GlowBeing*>();
    LOGI("%s %d: new %s", __FILE__, __LINE__, "vector of glowbeing*");
    std::vector<float>* angles = new std::vector<float>();
    LOGI("%s %d: new %s", __FILE__, __LINE__, "vector of float");
    std::vector<float>* rForParticle = new std::vector<float>();
    LOGI("%s %d: new %s", __FILE__, __LINE__, "vector of float");



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
        DustDevil* dustDevil = new DustDevil(r, h, inDustDevil, angles, rForParticle);
        LOGI("%s %d: new %s", __FILE__, __LINE__, "dustDevil");

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

        devil->Update(t_elapsed);

    }
    for (int i = dustDevils.size()-1; i >= 0; i--)
    {

        if (dustDevils[i]->phase == 1)
        {
            delete dustDevils[i];
            dustDevils.pop_back();
        }
    }
}
