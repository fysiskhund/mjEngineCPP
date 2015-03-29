#ifndef MJRENDEREDTEXT
#define MJRENDEREDTEXT

#include <string>

#include "../core/mjObject.h"
#include "mjTextureResource.h"

namespace mjEngine{


class mjRenderedText: public mjObject
{
public:
	mjTextureResource* fontMap;

    void SetFontMap(std::string& texturePath, int charWidth, int charHeight);
    void SetText(std::string& text);
	void SetText(const char* text);
};

}

#endif
