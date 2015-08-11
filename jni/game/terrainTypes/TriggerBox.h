#ifndef TRIGGERBOX_H
#define TRIGGERBOX_H

#include <core/mjObject.h>

using namespace mjEngine;

class TriggerBox: public mjObject
{
public:
    TriggerBox(mjResourceManager* resourceManager);
    virtual void SetDetailsFromXML(XMLElement* xmlElement) override;

    virtual ~TriggerBox();
};

#endif // TRIGGERBOX_H
