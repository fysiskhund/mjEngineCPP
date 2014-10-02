#!/bin/sh

g++ -DDESKTOP_SDL -g -std=c++11 -lSDL2 -lpng16 -lGLESv2 etc/main.cpp \
graphics/mjModel.cpp \
graphics/mjSceneGraph.cpp \
graphics/mjModelMesh.cpp \
graphics/mjShader.cpp \
graphics/mjSkybox.cpp \
graphics/mjCamera.cpp \
graphics/mjDefaultShaders.cpp \
graphics/mjSkyboxLevelData.cpp \
graphics/mjSkyboxShaders.cpp \
graphics/mjImageLoader.cpp \
graphics/mj3rdPersonCamera.cpp \
core/mjVector3.cpp \
core/mjObject.cpp \
extLibs/math/Matrix.cpp \
extLibs/math/mjMathHelper.cpp \
extLibs/tinyxml/tinyxml2.cpp \
physics/mjPhysicsEffect.cpp \
physics/mjSphere.cpp \
physics/mjPhysics.cpp \
physics/mjCollisionResult.cpp \
physics/mjAABB.cpp \
physics/mjCollisionTests.cpp \
terrainTypes/Box.cpp \
entities/Bird.cpp \
entities/Character.cpp \
EntityCreator.cpp \
TerrainCreator.cpp \
gl_code.cpp \
Level.cpp \
-o mjEngine.out
