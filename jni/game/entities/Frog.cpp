#include "Frog.h"

#include "frogAutomatonStates/FrogAutomatonStopState.h"
#include "frogAutomatonStates/FrogJumpAutomatonState.h"

Frog::Frog(Level* levelData, mjResourceManager* resourceManager)
: KosmoObject(MJ_AABB, resourceManager, levelData)
{
    srand(time(0));


    //model = resourceManager.FetchModel("frog.mesh.xml");
    //glTexture = resourceManager.FetchTexture("frog.png");

    model = resourceManager->FetchModel("entities/frog/frog.mesh.xml");

    glTexture = resourceManager->FetchTexture("entities/frog/frog.png", GL_REPEAT);//("/sdcard/mjEngineCPP/bluesky/wandering_cloud0.png"); //
	for (unsigned i = 0; i < model->meshes.size(); i++)
	{
		model->meshes[i]->glTexture = glTexture;
	}

    FrogAutomatonState* stopState = new FrogAutomatonStopState(this);
    LOGI("%s %d: new %s", __FILE__, __LINE__, "frogStopState");


    FrogAutomatonState* jumpState = new FrogAutomatonJumpState(this);
    LOGI("%s %d: new %s", __FILE__, __LINE__, "frogJumpState");


    states.push_back(stopState);
    states.push_back(jumpState);
    SetStartState(stopState);

    MatchAABBToModel();

    soundSource = new mjSoundSource();
    LOGI("%s %d: new %s", __FILE__, __LINE__, "soundSource");

    soundSource->Load(resourceManager->FetchSound("sounds/ribbit.wav"), 0);

    mass = 1000; // SO PHAT!


}

void Frog::Update(float t_elapsed)
{

	mjAutomaton::Update(t_elapsed);
    KosmoObject::UpdatePosition(t_elapsed);

}

Frog::FrogAutomatonState::FrogAutomatonState(Frog* frog)
{
    this->frog = frog;
}


void Frog::SetDetailsFromXML(XMLElement* entity)
{
    KosmoObject::SetDetailsFromXML(entity);
    startPosition.CopyFrom(pos);
    mjAABB* mjaabbStruct = (mjAABB*) boundingStructure;
    mjaabbStruct->UpdateCorners();
}
