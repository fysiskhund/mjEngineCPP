#ifndef FALLINGBOX_H
#define FALLINGBOX_H

#include <vector>
#include "Box.h"
#include <audio/mjSoundSource.h>


// The "falling box" should really be called "scriptable box"
// It has two behaviours, one is that it travels along a specific direction once it is set in motion
// The other is that if control points are specified, it will travel between them.

class FallingBox: public Box
{
    public:
        float totalTimeToFall = 3; // 3s-
        float timeToFall = 0;
        float totalTimeToReturn = 0;
        float timeToReturn = 0;
        int fallingState = 0;
        bool hasWeight = 0;
        bool timeToFallIsAccumulative = false;
        bool slidingSoundPlaying = false;

        mjVector3 startPosition;
        mjVector3 gravity;
        mjVector3 gravityNormalized;
        mjVector3 travelDirection;
        mjSoundSource cinderBlockSlide;


        FallingBox(mjResourceManager& resourceManager);

        int currentControlPointIndex = 1;
        bool active = false;
        std::vector<mjVector3*> controlPoints;

        virtual void SetDetailsFromXML(XMLElement* fallingBoxElem) override;
        virtual void ProcessCollisionEffects() override;
        virtual void ProcessPhysicsEffects(float t_elapsed) override;
        virtual void Update(float t_elapsed) override;

        void Reset();

        virtual ~FallingBox();
    protected:
    private:
};

#endif // FALLINGBOX_H
