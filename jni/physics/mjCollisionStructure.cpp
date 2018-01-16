#include "mjCollisionStructure.h"

namespace mjEngine{

mjCollisionStructure::mjCollisionStructure()
{
    //ctor
}

void mjCollisionStructure::AddObject(mjObject* obj)
{
    objects.push_back(obj);
}

void mjCollisionStructure::CreateBoundaries()
{

}

void mjCollisionStructure::Update(double t_elapsed)
{

}

mjCollisionStructure::~mjCollisionStructure()
{
    //dtor
}

}
