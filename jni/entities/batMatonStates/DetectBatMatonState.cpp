#include "DetectBatMatonState.h"

DetectBatMatonState::DetectBatMatonState(BatBot* bat)
:BatBot::BatAutomatonState::BatAutomatonState(bat)
{

	player = bat->levelData->GetEntityByID("character0");

}

DetectBatMatonState::~DetectBatMatonState()
{
    //dtor
}
