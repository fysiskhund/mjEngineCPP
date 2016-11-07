TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = mjEngine

include(deployment.pri)
qtcAddDeployment()

QMAKE_CXXFLAGS += -std=c++11

DEFINES -= UNICODE
#DEFINES += DESKTOP_SDL NON_GLES_CONTEXT USE_SDL_AUDIO USE_GL3 #USE_ASSIMP #DEBUGCOLLISIONS
DEFINES += DESKTOP_SDL USE_GLES2 USE_SDL_AUDIO #DEBUGCOLLISIONS

win32: DEFINES += WIN32
win32: DEFINES -= UNICODE
unix: DEFINES += GNULINUX

HEADERS += \
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
    extLibs/tinyxml/tinyxml2.h \
    extLibs/util/mjMultiPlatform.h \
    extLibs/util/mjMultiPlatformAudio.h \
    extLibs/util/mjXMLHelper.h \
    etc/testImage.h \
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
    util/mjResource.h \
    util/mjResourceManager.h \
    util/mjSoundResource.h \
    util/mjTextureResource.h \
    graphics/mjAssimpModel.h \
    graphics/renderer/mjRenderer.h \
    graphics/renderer/mjRendererData.h \
    graphics/renderer/mjRendererDataGL.h \
    graphics/renderer/mjRendererGL.h \
    util/mjShaderResource.h \
    input/mjInputEvent.h \
    text/mjTextShaders.h \
    extLibs/utf8-utils/utf8-utils.h \
    text/mjGraphicCharObject.h \
    util/mjFontResource.h \
    text/mjGraphicText.h \
    util/mjGraphicCharObjectResource.h

SOURCES += \
    ai/mjAutomaton.cpp \
    ai/mjAutomatonState.cpp \
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
    extLibs/math/Matrix.cpp \
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
    util/mjResource.cpp \
    util/mjResourceManager.cpp \
    util/mjSoundResource.cpp \
    util/mjTextureResource.cpp \
    graphics/mjAssimpModel.cpp \
    graphics/renderer/mjRenderer.cpp \
    graphics/renderer/mjRendererData.cpp \
    graphics/renderer/mjRendererDataGL.cpp \
    graphics/renderer/mjRendererGL.cpp \
    util/mjShaderResource.cpp \
    input/mjInputEvent.cpp \
    text/mjTextShaders.cpp \
    extLibs/utf8-utils/utf8-utils.c \
    text/mjGraphicCharObject.cpp \
    util/mjFontResource.cpp \
    text/mjGraphicText.cpp \
    util/mjGraphicCharObjectResource.cpp



INCLUDEPATH += $$PWD/../../../sdl/i686-w64-mingw32/include $$PWD/../../../glew/include

win32: LIBS += -L$$PWD/../../../glew/lib/Release/Win32/ -L$$PWD/../../../sdl/i686-w64-mingw32/lib/

win32: LIBS += -lmingw32 -mwindows -lSDL2main -lSDL2 -lSDL2_image -lglew32s -lopengl32 -lSDL2_mixer

#linux: LIBS += -lSDL2 -lGL -lGLEW -lSDL2_image -lSDL2_mixer


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += sdl2 glew gl libpng SDL2_image SDL2_mixer assimp freetype2 #for GL3 rendering
#unix: PKGCONFIG += sdl2 glesv2 libpng SDL2_image SDL2_mixer #for GLESv2 rendering
