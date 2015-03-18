#ifndef MJRENDEREDTEXT
#define MJRENDEREDTEXT

#include <string>
#include "../core/mjObject.h"

namespace mjEngine{


class mjRenderedText: public mjObject
{
public:
	mjTextureResource* fontMap;

	void SetFontMap(string& texturePath, int charWidth, int charHeight);
	void SetText(string& text);
	void SetText(const char* text);
};

}

#endif
