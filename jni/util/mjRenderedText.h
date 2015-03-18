#ifndef MJRENDEREDTEXT
#define MJRENDEREDTEXT

#include <string>
#include "../core/mjObject.h"

namespace mjEngine{


class mjRenderedText: public mjObject
{
public:
	void SetText(string& text);
	void SetText(const char* text);
};

}

#endif
