#ifndef FROG_H
#define FROG_H


#include <vector>
#include <time.h>
#include <stdlib.h>

#include <core/mjObject.h>
#include <game/Level.h>
#include <ai/mjAutomaton.h>
#include <extLibs/util/mjXMLHelper.h>
#include <audio/mjSoundSource.h>

#include "KosmoObject.h"

class Frog : public KosmoObject, public mjAutomaton
{
    public:
        Frog(Level* levelData, mjResourceManager* resourceManager);
        void SetDetailsFromXML(XMLElement* entity) override;
        void Update(float t_elapsed) override;
        unsigned glTexture;
        mjVector3 jumpDirection;
        mjSoundSource* soundSource;


class FrogAutomatonState: public mjAutomatonState
        {
        public:
            FrogAutomatonState(Frog* frog);
            Frog* frog;
        };

    protected:
    private:
};



#endif // FROG_H
