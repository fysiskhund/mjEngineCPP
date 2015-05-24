#ifndef BATBOT_H
#define BATBOT_H

#include <math.h>
#include <vector>
#include <extLibs/math/MathConstants.h>


#include <core/mjObject.h>
#include <game/Level.h>
#include <ai/mjAutomaton.h>
#include <extLibs/util/mjXMLHelper.h>
#include <graphics/animation/mjAnimation.h>
#include <graphics/animation/mjAnimationKeyframe.h>
#include <graphics/animation/mjAnimator.h>
#include <graphics/animation/mjModelAnimation.h>
#include <graphics/animation/mjModelPose.h>
//#include <ai/mjAutomatonState>




using namespace mjEngine;

enum batMatonStates{
  BM_WANDER=0, BM_DETECT, BM_ATTACK
};


class BatBot: public mjObject, public mjAutomaton
{
    public:

        mjAnimation animation;
        mjAnimator animator;
        float tAnimation = 0;

        BatBot(Level* levelData, mjResourceManager* resourceManager);
        //BatBot(const BatBot& other);
        Level* levelData;

        float wanderRadiusMin = 1;
        float wanderRadiusMax = 8;
        float attackDistance = 4;
        mjVector3 wanderDir;
        mjVector3 anchor;
        mjVector3 attackVector;



        bool ignoresGravity = true;

        virtual void Update(float t_elapsed) override;

        //virtual void ProcessCollisionEffects() override;

        virtual void ProcessPhysicsEffects(float t_elapsed) override;
        virtual void SetDetailsFromXML(XMLElement* entity) override;


        class BatAutomatonState: public mjAutomatonState
        {
        public:
            BatAutomatonState(BatBot* bat);
            BatBot* bat;
        };


    protected:
    private:
};





#endif // BATBOT_H
