TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


include(deployment.pri)
qtcAddDeployment()

QMAKE_CXXFLAGS += -std=c++11

DEFINES -= UNICODE
#DEFINES += DESKTOP_SDL NON_GLES_CONTEXT USE_SDL_AUDIO USE_GL3 #USE_ASSIMP #DEBUGCOLLISIONS
DEFINES += DESKTOP_SDL USE_GL3 USE_SDL_AUDIO #DEBUGCOLLISIONS

win32: DEFINES += WIN32
win32: DEFINES -= UNICODE
unix: DEFINES += GNULINUX

HEADERS += \
    ../keyboardcontrol.h \
    ai/mjAutomaton.h \
    ai/mjAutomatonState.h \
    audio/mjMusicPlayer.h \
    audio/mjSoundSource.h \
    core/mjInput.h \
    core/mjObject.h \
    core/mjScene.h \
    core/mjSceneManager.h \
    core/mjVector3.h \
    extLibs/logger/mjLog.h \
    extLibs/math/mjMathHelper.h \
    extLibs/math/mjMatrixStack.h \
    extLibs/png/include/png.h \
    extLibs/tinyxml/tinyxml2.h \
    extLibs/util/mjMultiPlatform.h \
    extLibs/util/mjMultiPlatformAudio.h \
    extLibs/util/mjXMLHelper.h \
    extLibs/math/MathConstants.h \
    extLibs/math/Matrix.h \
    graphics/animation/mjAnimation.h \
    graphics/animation/mjAnimationKeyframe.h \
    graphics/animation/mjAnimationSegment.h \
    graphics/animation/mjAnimator.h \
    graphics/animation/mjModelAnimation.h \
    graphics/animation/mjModelPose.h \
    graphics/animation/mjModelStructure.h \
    graphics/animation/mjModelStructureNode.h \
    graphics/gl3/defaultShaderSources-gl3.h \
    graphics/gl3/skyboxShaderSources-gl3.h \
    graphics/mj3rdPersonCamera.h \
    graphics/mjCamera.h \
    graphics/mjDefaultShaders.h \
    graphics/mjImageLoader.h \
    graphics/mjModel.h \
    graphics/mjModelMesh.h \
    graphics/mjSceneGraph.h \
    graphics/mjShader.h \
    graphics/mjSkybox.h \
    graphics/mjSkyboxLevelData.h \
    graphics/mjSkyboxShaders.h \
    physics/mjAABB.h \
    physics/mjBoundingStructure.h \
    physics/mjCollisionResult.h \
    physics/mjCollisionStructure.h \
    physics/mjCollisionTests.h \
    physics/mjPhysics.h \
    physics/mjPhysicsEffect.h \
    physics/mjSphere.h \
    util/mjModelResource.h \
    util/mjModelStructureResource.h \
    util/mjRenderedText.h \
    util/mjResource.h \
    util/mjResourceManager.h \
    util/mjSoundResource.h \
    util/mjTextureResource.h \
    graphics/mjAssimpModel.h \
    game/ambient/DustDevil.h \
    game/entities/batMatonStates/AttackBatMatonState.h \
    game/entities/batMatonStates/DetectBatMatonState.h \
    game/entities/batMatonStates/WanderBatMatonState.h \
    game/entities/frogAutomatonStates/FrogAutomatonStopState.h \
    game/entities/frogAutomatonStates/FrogJumpAutomatonState.h \
    game/entities/BatBot.h \
    game/entities/BatMaton.h \
    game/entities/Bird.h \
    game/entities/Character.h \
    game/entities/Frog.h \
    game/entities/GlowBeing.h \
    game/entities/MysticalDoor.h \
    game/entities/Plant.h \
    game/terrainTypes/Box.h \
    game/terrainTypes/FallingBox.h \
    game/windStates/DustDevilState.h \
    game/windStates/SteadyDirectionState.h \
    game/windStates/WindState.h \
    game/entities/KosmoObject.h \
    game/ObjectTags.h \
    game/entities/FrogBoss.h \
    game/entities/frogBossAutomatonStates/FrogBossAutomatonHuntState.h \
    game/entities/frogBossAutomatonStates/FrogBossAutomatonSlamState.h \
    game/entities/frogBossAutomatonStates/FrogBossAutomatonWaitForLandingState.h \
    game/terrainTypes/TriggerBox.h \
    game/entities/Baobab.h \
    graphics/mjAssimpModel.h

SOURCES += \
    game/Ambient.cpp \
    game/EntityCreator.cpp \
    game/gl_code.cpp \
    game/Level.cpp \
    game/PlatformUniverseScene.cpp \
    game/TerrainCreator.cpp \
    game/ambient/DustDevil.cpp \
    game/entities/batMatonStates/AttackBatMatonState.cpp \
    game/entities/batMatonStates/DetectBatMatonState.cpp \
    game/entities/batMatonStates/WanderBatMatonState.cpp \
    game/entities/frogAutomatonStates/FrogAutomatonStopState.cpp \
    game/entities/frogAutomatonStates/FrogJumpAutomatonState.cpp \
    game/entities/BatBot.cpp \
    game/entities/BatMaton.cpp \
    game/entities/Bird.cpp \
    game/entities/Character.cpp \
    game/entities/Frog.cpp \
    game/entities/GlowBeing.cpp \
    game/entities/MysticalDoor.cpp \
    game/entities/Plant.cpp \
    game/terrainTypes/Box.cpp \
    game/terrainTypes/FallingBox.cpp \
    game/windStates/DustDevilState.cpp \
    game/windStates/SteadyDirectionState.cpp \
    game/windStates/WindState.cpp \
    gnuLinux/keyboardcontrol.cpp \
    gnuLinux/main.cpp \
    game/entities/KosmoObject.cpp \
    game/entities/FrogBoss.cpp \
    game/entities/frogBossAutomatonStates/FrogBossAutomatonHuntState.cpp \
    game/entities/frogBossAutomatonStates/FrogBossAutomatonSlamState.cpp \
    game/entities/frogBossAutomatonStates/FrogBossAutomatonWaitForLandingState.cpp \
    game/terrainTypes/TriggerBox.cpp \
    game/entities/Baobab.cpp


INCLUDEPATH += $$PWD/../

win32: LIBS += -L$$PWD/../precompiled/mjEngine/win32 -lmjEngine

win32: INCLUDEPATH += $$PWD/../../../../sdl/i686-w64-mingw32/include $$PWD/../../../../glew/include $$PWD/../extLibs/freetype2/include

win32: LIBS += -L$$PWD/../../../../glew/lib/Release/Win32/ -L$$PWD/../../../../sdl/i686-w64-mingw32/lib/ -L$$PWD/../precompiled/freetype2/win32/ -lfreetype



win32: LIBS += -lmingw32 -mwindows -lSDL2main -lSDL2 -lSDL2_image -lglew32s -lopengl32 -lSDL2_mixer

#linux: LIBS += -lSDL2 -lGL -lGLEW -lSDL2_image -lSDL2_mixer



unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += sdl2 glew gl libpng SDL2_image SDL2_mixer freetype2 #assimp #for GL3 rendering
#unix: PKGCONFIG += sdl2 glesv2 libpng SDL2_image SDL2_mixer #for GLESv2 rendering

linux: LIBS += -L$$PWD/precompiled/mjEngine/pc-linux-x86_64/ -lmjEngine
