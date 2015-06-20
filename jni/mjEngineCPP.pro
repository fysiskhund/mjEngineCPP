TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


include(deployment.pri)
qtcAddDeployment()

QMAKE_CXXFLAGS += -std=c++11 -static

DEFINES -= UNICODE
DEFINES += DESKTOP_SDL NON_GLES_CONTEXT USE_SDL_AUDIO USE_GL3 DEBUGCOLLISIONS

win32: DEFINES += WIN32
unix: DEFINES += GNULINUX

HEADERS += \
    ../keyboardcontrol.h \
    ai/mjAutomaton.h \
    ai/mjAutomatonState.h \
    audio/sdl/mjMusicPlayer_SDL.h \
    audio/sdl/mjSoundSource_SDL.h \
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
    extLibs/tinyxml/tinyxml2.h \
    extLibs/util/mjMultiPlatform.h \
    extLibs/util/mjMultiPlatformAudio.h \
    extLibs/util/mjXMLHelper.h \
    game/Ambient.h \
    game/EntityCreator.h \
    game/gl_code.h \
    game/Level.h \
    game/PlatformUniverseScene.h \
    game/TerrainCreator.h \
    etc/testImage.h \
    extLibs/math/MathConstants.h \
    extLibs/math/Matrix.h \
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
    game/entities/KosmoObject.h \
    game/ObjectTags.h

SOURCES += \
    ai/mjAutomaton.cpp \
    ai/mjAutomatonState.cpp \
    audio/sdl/mjMusicPlayer_SDL.cpp \
    audio/sdl/mjSoundSource_SDL.cpp \
    audio/mjMusicPlayer.cpp \
    audio/mjSoundSource.cpp \
    core/mjObject.cpp \
    core/mjScene.cpp \
    core/mjSceneManager.cpp \
    core/mjVector3.cpp \
    extLibs/math/mjMathHelper.cpp \
    extLibs/math/mjMatrixStack.cpp \
    extLibs/tinyxml/tinyxml2.cpp \
    extLibs/util/mjMultiPlatform.cpp \
    extLibs/util/mjXMLHelper.cpp \
    game/Ambient.cpp \
    game/EntityCreator.cpp \
    game/gl_code.cpp \
    game/Level.cpp \
    game/PlatformUniverseScene.cpp \
    game/TerrainCreator.cpp \
    extLibs/math/Matrix.cpp \
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
    graphics/animation/mjAnimation.cpp \
    graphics/animation/mjAnimationKeyframe.cpp \
    graphics/animation/mjAnimationSegment.cpp \
    graphics/animation/mjAnimator.cpp \
    graphics/animation/mjModelAnimation.cpp \
    graphics/animation/mjModelPose.cpp \
    graphics/animation/mjModelStructure.cpp \
    graphics/animation/mjModelStructureNode.cpp \
    graphics/mj3rdPersonCamera.cpp \
    graphics/mjCamera.cpp \
    graphics/mjDefaultShaders.cpp \
    graphics/mjImageLoader.cpp \
    graphics/mjModel.cpp \
    graphics/mjModelMesh.cpp \
    graphics/mjSceneGraph.cpp \
    graphics/mjShader.cpp \
    graphics/mjSkybox.cpp \
    graphics/mjSkyboxLevelData.cpp \
    graphics/mjSkyboxShaders.cpp \
    physics/mjAABB.cpp \
    physics/mjCollisionResult.cpp \
    physics/mjCollisionStructure.cpp \
    physics/mjCollisionTests.cpp \
    physics/mjPhysics.cpp \
    physics/mjPhysicsEffect.cpp \
    physics/mjSphere.cpp \
    util/mjModelResource.cpp \
    util/mjModelStructureResource.cpp \
    util/mjRenderedText.cpp \
    util/mjResource.cpp \
    util/mjResourceManager.cpp \
    util/mjSoundResource.cpp \
    util/mjTextureResource.cpp \
    game/entities/KosmoObject.cpp



INCLUDEPATH += $$PWD/../../../sdl/i686-w64-mingw32/include $$PWD/../../../glew/include

win32: LIBS += -L$$PWD/../../../glew/lib/Release/Win32/ -L$$PWD/../../../sdl/i686-w64-mingw32/lib/

win32: LIBS += -lmingw32 -mwindows -lSDL2main -lSDL2 -lSDL2_image -lglew32s -lopengl32 -lSDL2_mixer

#linux: LIBS += -lSDL2 -lGL -lGLEW -lSDL2_image -lSDL2_mixer


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += sdl2 glew gl libpng SDL2_image SDL2_mixer
