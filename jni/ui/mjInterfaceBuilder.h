#ifndef MJINTERFACEBUILDER_H
#define MJINTERFACEBUILDER_H

#include "../extLibs/tinyxml/tinyxml2.h"
#include "../extLibs/logger/mjLog.h"
#include "../core/mjObject.h"
#include "../graphics/mjSceneGraph.h"


// UI components
#include "../text/mjGraphicText.h"

//

using namespace tinyxml2;
using namespace mjEngine;


class mjInterfaceBuilder
{
public:
    XMLDocument doc;
    std::vector<mjObject*> uiObjects;

    mjResourceManager* resourceManager;
    mjSceneGraph* sceneGraph;
    std::string fontName = "fonts/NotoMono-Regular.ttf";
    int fontSize = 42;
    TextAlignment textAlignment = ALIGNMENT_LEFT;
    float renderScale = 0.002;
    float positionScaleHz = 0.0022;
    float positionScaleVr = 0.0021;




    mjInterfaceBuilder();
    virtual ~mjInterfaceBuilder();
    void LoadFromPath(const char* path, mjResourceManager* resourceManager, mjSceneGraph* sceneGraph);
    void LoadFromMemory(const unsigned char* xmlContents, size_t length, mjResourceManager* resourceManager, mjSceneGraph* sceneGraph);
    virtual mjObject* BuildObject(XMLElement* entity);

};

#endif // INTERFACEBUILDER_H
