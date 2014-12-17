#ifndef FALLINGBOX_H
#define FALLINGBOX_H

#include "Box.h"

class FallingBox: public Box
{
    public:
        float totalTimeToFall = 3; // 3s-
        float timeToFall = 0;
        int fallingState = 0;
        bool hasWeight = 0;
        mjVector3 startPosition;
        FallingBox(mjResourceManager& resourceManager);
        virtual void SetDetailsFromXML(XMLElement* fallingBoxElem) override;
        virtual void ProcessCollisionEffects() override;
        virtual void Update(float t_elapsed) override;

        virtual ~FallingBox();
    protected:
    private:
};

#endif // FALLINGBOX_H
