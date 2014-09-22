#ifndef CHARACTER_H
#define CHARACTER_H

#include "core/mjObject.h"
using namespace mjEngine;


class Character: public mjObject
{
public:
	Character(structuretype type);
	int footing;
};


#endif
