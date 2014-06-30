#include <string.h>

#include <stdio.h>

#include "mjVector3.h"
#include "graphics/mjModel.h"

using namespace mjEngine;

int main(int argc, char** argv)
{
   mjModel* model = new mjModel();
   model->LoadFromFile("../etc/sprite.mesh.xml");
   printf(model->status);
   return 0;
}
