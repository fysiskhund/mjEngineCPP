#include "Frog.h"

#include "frogAutomatonStates/FrogAutomatonStopState.h"
#include "frogAutomatonStates/FrogJumpAutomatonState.h"

Frog::Frog(Level* levelData, mjResourceManager& resourceManager):
mjObject(MJ_AABB)
{
    srand(time(0));
    this->levelData = levelData;


    //model = resourceManager.FetchModel("frog.mesh.xml");
    //glTexture = resourceManager.FetchTexture("frog.png");

    model = resourceManager.FetchModel("frog.mesh.xml");

    glTexture = resourceManager.FetchTexture("frog.png");//("/sdcard/mjEngineCPP/bluesky/wandering_cloud0.png"); //
	for (unsigned i = 0; i < model->meshes.size(); i++)
	{
		model->meshes[i]->glTexture = glTexture;
	}

    FrogAutomatonState* stopState = new FrogAutomatonStopState(this);
    FrogAutomatonState* jumpState = new FrogAutomatonJumpState(this);

    states.push_back(stopState);
    states.push_back(jumpState);
    SetStartState(stopState);

    MatchAABBToModel();

    soundSource = new mjSoundSource();
    soundSource->Load(resourceManager.FetchSound("sounds/ribbit.wav"), 0);



}

void Frog::Update(float t_elapsed)
{

	mjAutomaton::Update(t_elapsed);
	mjObject::UpdatePosition(t_elapsed);

}

Frog::FrogAutomatonState::FrogAutomatonState(Frog* frog)
{
    this->frog = frog;
}


void Frog::SetDetailsFromXML(XMLElement* entity)
{
    mjObject::SetDetailsFromXML(entity);
    startPosition.CopyFrom(pos);
    mjAABB* mjaabbStruct = (mjAABB*) boundingStructure;
    mjaabbStruct->UpdateCorners();
}
