#ifndef FROGBOSS_H
#define FROGBOSS_H


#include <vector>
#include <time.h>
#include <stdlib.h>

#include <core/mjObject.h>
#include <game/Level.h>
#include <ai/mjAutomaton.h>
#include <extLibs/util/mjXMLHelper.h>
#include <audio/mjSoundSource.h>

#include "KosmoObject.h"

class FrogBoss : public KosmoObject, public mjAutomaton
{
    public:
        FrogBoss(Level* levelData, mjResourceManager* resourceManager);
        void SetDetailsFromXML(XMLElement* entity) override;
        void Update(double t_elapsed) override;
        void ProcessCollisionEffects() override;
        void ResetByDefeat();
        void Reset();

        unsigned glTexture;

        KosmoObject* target = NULL;
        mjVector3 launchLocation;
        mjVector3 slamLocation;
        mjVector3 gravity;

        mjSoundSource* soundSource;

        bool firstTimeTargetSeen = true;
        bool wasDefeated = false;
        int defeatedTimes = 0;
        int berserkTimes = 0;


        int hasFooting = 0;
        bool LAME_FIX_alreadyProcessedSpeedForThisFrame = false;


class FrogBossAutomatonState: public mjAutomatonState
        {
        public:
            FrogBossAutomatonState(FrogBoss* frogBoss);
            FrogBoss* frogBoss;
        };

    protected:
    private:
};



#endif // FROG_H
