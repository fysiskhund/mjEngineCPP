#include "mjInterfaceBuilder.h"

mjInterfaceBuilder::mjInterfaceBuilder()
{
    internalMessenger = new mjInternalMessenger();
}

mjInterfaceBuilder::~mjInterfaceBuilder()
{
    for(unsigned int i = 0; i < uiObjects.size(); i++)
    {
        internalMessenger->Unsubscribe(uiObjects[i]);
        delete uiObjects[i];
    }
    uiObjects.empty();
    delete internalMessenger;
}

void mjInterfaceBuilder::LoadFromPath(const char* path, mjResourceManager* resourceManager, mjSceneGraph* sceneGraph)
{
    std::string fullPath = path;

    resourceManager->PrependFullFilePath(fullPath);


    const unsigned char* buffer;
    size_t readSize;

    mjFileFromArchive* xmlFileFromArchive = resourceManager->ReadAllFromArchiveToBuffer(fullPath.c_str(), &buffer, &readSize);

    LoadFromMemory(buffer, readSize, resourceManager, sceneGraph);
    resourceManager->CloseAndFreeResources(&xmlFileFromArchive);
}


void mjInterfaceBuilder::LoadFromMemory(const unsigned char* xmlContents, size_t length, mjResourceManager* resourceManager, mjSceneGraph* sceneGraph)
{
    this->resourceManager = resourceManager;
    this->sceneGraph = sceneGraph;

    doc.Parse((const char*)xmlContents, length);
    XMLHandle docHandle(doc);

    XMLElement* uiElement = docHandle.FirstChildElement("ui").FirstChildElement().ToElement();

    // Read default values for this UI (font, fontSize, etc.)

    const char* value = uiElement->Attribute("font");
    if (value)
        fontName = value;

    uiElement->QueryIntAttribute("fontSize", &fontSize);


    std::string textAlignmentAttr;

    value = uiElement->Attribute("textAlignment");
    if (value)
        textAlignmentAttr= value;

    uiElement->QueryFloatAttribute("renderScale", &renderScale);
    uiElement->QueryFloatAttribute("positionScaleHz", &positionScaleHz);
    uiElement->QueryFloatAttribute("positionScaleVr", &positionScaleVr);


    if (textAlignmentAttr.compare("center") == 0)
    {
        textAlignment = ALIGNMENT_CENTER;
    } else if (textAlignmentAttr.compare("right") == 0)
    {
        textAlignment = ALIGNMENT_RIGHT;
    } else
    {
        textAlignment = ALIGNMENT_LEFT;
    }



    XMLElement* child = uiElement->FirstChildElement();

    while (child != NULL)
    {
        mjObject* newObject = BuildObject(child);
        if (newObject != NULL)
        {
            if (!newObject->variable.empty())
            {
                internalMessenger->Subscribe(newObject);
            }

            uiObjects.push_back(newObject);
        }
        child = child->NextSiblingElement();
    }
    // All done


}

mjObject* mjInterfaceBuilder::BuildObject(XMLElement* entity)
{

    mjObject* newObject = NULL;


    if (strncmp(entity->Name(), "text", strnlen(entity->Name(), 64)) == 0)
    {
        // Read atttributes for this text (font, fontSize, etc.)

        TextAlignment localTextAlignment = textAlignment;
        std::string localFontName = fontName;

        const char* value = entity->Attribute("font");
        if (value)
        {
            localFontName = entity->Attribute("font");;
        }

        int localFontSize = fontSize;
        float localRenderScale = renderScale;
        float localPositionScaleHz = positionScaleHz;
        float localPositionScaleVr = positionScaleVr;
        float fontColor[] = {1, 1, 1, 1};
        mjVector3 position;

        value = entity->Attribute("textAlignment");

        if (value)
        {
            if (strncmp(value, "center", 16) == 0)
            {
                localTextAlignment = ALIGNMENT_CENTER;
            } else if (strncmp(value, "right", 16) == 0)
            {
                localTextAlignment = ALIGNMENT_RIGHT;
            } else if (strncmp(value, "left", 16) == 0)
            {
                localTextAlignment = ALIGNMENT_LEFT;
            } // Else do not change from the default value.
        }

        mjVector3 fontPosition; // later to be filled by mjObject's xml details reafiong, no need to care about it here.

        entity->QueryIntAttribute("fontSize", &localFontSize);
        entity->QueryFloatAttribute("renderScale", &localRenderScale);
        entity->QueryFloatAttribute("positionScaleHz", &localPositionScaleHz);
        entity->QueryFloatAttribute("positionScaleVr", &localPositionScaleVr);



        const char* text = entity->Attribute("content");

        newObject = new mjGraphicText(resourceManager, text, localFontName.c_str(), localFontSize,
                                      localRenderScale, localPositionScaleHz, localPositionScaleVr,
                                      fontColor, fontPosition, localTextAlignment);

    } else if (strncmp(entity->Name(), "img", strnlen(entity->Name(), 64)) == 0)
    {
        const char* source = entity->Attribute("src");
        const char* model = entity->Attribute("model");


        newObject = new mjObject(resourceManager, MJ_NO_BOUNDING_STRUCT);
        if (model)
        {
            newObject->model = resourceManager->FetchModel(model);
        } else
        {
            newObject->model = resourceManager->FetchModel("models/sprite.mesh.xml");
        }
        newObject->customTextures = new GLuint[1];
        GLuint texture = resourceManager->FetchTexture(source);
        newObject->customTextures[0] = texture;


    } else if (strncmp(entity->Name(), "button", strnlen(entity->Name(), 64)) == 0)
    {
        LOGI("Here goes a button :3 ");
    }

    if (newObject)
    {
        newObject->SetDetailsFromXML(entity);
    }
    return newObject;
}

void mjInterfaceBuilder::Update(double t_elapsed)
{
    for (int i = 0; i < uiObjects.size(); i++)
    {
        uiObjects[i]->Update(t_elapsed);
    }
}
