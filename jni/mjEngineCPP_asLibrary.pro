TEMPLATE = lib
CONFIG += console

win32: CONFIG += static

CONFIG -= app_bundle
CONFIG -= qt

TARGET = mjEngine

include(deployment.pri)
qtcAddDeployment()

QMAKE_CXXFLAGS += -std=c++11

DEFINES -= UNICODE
#DEFINES += DESKTOP_SDL NON_GLES_CONTEXT USE_SDL_AUDIO USE_GL3 #USE_ASSIMP #DEBUGCOLLISIONS
DEFINES += DESKTOP_SDL USE_GL3 USE_SDL_AUDIO DEBUGONBEFOREDRAW #DEBUGCOLLISIONS

win32: DEFINES += WIN32
unix: DEFINES += GNULINUX

# mjEngine path
unix: MJENGINE=/common/fh/mjEngineCPP/jni
win32: MJENGINE=c:/common/fh/mjEngineCPP/jni

HEADERS += \
    $${MJENGINE}/ai/mjAutomaton.h \
    $${MJENGINE}/ai/mjAutomatonState.h \
    $${MJENGINE}/audio/mjMusicPlayer.h \
    $${MJENGINE}/audio/mjSoundSource.h \
    $${MJENGINE}/core/mjGameState.h \
    $${MJENGINE}/core/mjInput.h \
    $${MJENGINE}/core/mjObject.h \
    $${MJENGINE}/core/mjTransitionUniverse.h \
    $${MJENGINE}/core/mjUniverse.h \
    $${MJENGINE}/core/mjUniverseSwitcher.h \
    $${MJENGINE}/core/mjVector3.h \
    $${MJENGINE}/extLibs/logger/mjLog.h \
    $${MJENGINE}/extLibs/math/MathConstants.h \
    $${MJENGINE}/extLibs/math/Matrix.h \
    $${MJENGINE}/extLibs/math/mjMathHelper.h \
    $${MJENGINE}/extLibs/math/mjMatrixStack.h \
    $${MJENGINE}/extLibs/png/include/png.h \
    $${MJENGINE}/extLibs/tinyxml/tinyxml2.h \
    $${MJENGINE}/extLibs/utf8-utils/utf8-utils.h \
    $${MJENGINE}/extLibs/util/mjMultiPlatform.h \
    $${MJENGINE}/extLibs/util/mjMultiPlatformAudio.h \
    $${MJENGINE}/extLibs/util/mjXMLHelper.h \
    $${MJENGINE}/graphics/animation/mjAnimation.h \
    $${MJENGINE}/graphics/animation/mjAnimationKeyframe.h \
    $${MJENGINE}/graphics/animation/mjAnimationSegment.h \
    $${MJENGINE}/graphics/animation/mjAnimator.h \
    $${MJENGINE}/graphics/animation/mjModelAnimation.h \
    $${MJENGINE}/graphics/animation/mjModelPose.h \
    $${MJENGINE}/graphics/animation/mjModelStructure.h \
    $${MJENGINE}/graphics/animation/mjModelStructureNode.h \
    $${MJENGINE}/graphics/gl3/defaultShaderSources-gl3.h \
    $${MJENGINE}/graphics/gl3/skyboxShaderSources-gl3.h \
    $${MJENGINE}/graphics/mj3rdPersonCamera.h \
    $${MJENGINE}/graphics/mjAssimpModel.h \
    $${MJENGINE}/graphics/mjCamera.h \
    $${MJENGINE}/graphics/mjDefaultShaders.h \
    $${MJENGINE}/graphics/mjImageLoader.h \
    $${MJENGINE}/graphics/mjMaterialBucket.h \
    $${MJENGINE}/graphics/mjModel.h \
    $${MJENGINE}/graphics/mjModelMesh.h \
    $${MJENGINE}/graphics/mjSceneGraph.h \
    $${MJENGINE}/graphics/mjShader.h \
    $${MJENGINE}/graphics/mjSkybox.h \
    $${MJENGINE}/graphics/mjSkyboxLevelData.h \
    $${MJENGINE}/graphics/mjSkyboxShaders.h \
    $${MJENGINE}/graphics/renderer/mjRenderer.h \
    $${MJENGINE}/graphics/renderer/mjRendererData.h \
    $${MJENGINE}/graphics/renderer/mjRendererDataGL.h \
    $${MJENGINE}/graphics/renderer/mjRendererGL.h \
    $${MJENGINE}/input/mjInputEvent.h \
    $${MJENGINE}/internalMessaging/mjInternalMessageReceiver.h \
    $${MJENGINE}/internalMessaging/mjInternalMessenger.h \
    $${MJENGINE}/physics/mjAABB.h \
    $${MJENGINE}/physics/mjBoundingStructure.h \
    $${MJENGINE}/physics/mjCollisionResult.h \
    $${MJENGINE}/physics/mjCollisionStructure.h \
    $${MJENGINE}/physics/mjCollisionTests.h \
    $${MJENGINE}/physics/mjPhysics.h \
    $${MJENGINE}/physics/mjPhysicsEffect.h \
    $${MJENGINE}/physics/mjSphere.h \
    $${MJENGINE}/text/mjGraphicCharObject.h \
    $${MJENGINE}/text/mjGraphicText.h \
    $${MJENGINE}/text/mjTextShaders.h \
    $${MJENGINE}/ui/mjInterfaceBuilder.h \
    $${MJENGINE}/util/mjFileFromArchive.h \
    $${MJENGINE}/util/mjFontResource.h \
    $${MJENGINE}/util/mjGraphicCharObjectResource.h \
    $${MJENGINE}/util/mjModelResource.h \
    $${MJENGINE}/util/mjModelStructureResource.h \
    $${MJENGINE}/util/mjObjectPool.h \
    $${MJENGINE}/util/mjResource.h \
    $${MJENGINE}/util/mjResourceManager.h \
    $${MJENGINE}/util/mjShaderResource.h \
    $${MJENGINE}/util/mjSoundResource.h \
    $${MJENGINE}/util/mjTextureResource.h \
    $${MJENGINE}/ui/mjUIObject.h


SOURCES += \
    $${MJENGINE}/ai/mjAutomaton.cpp \
    $${MJENGINE}/ai/mjAutomatonState.cpp \
    $${MJENGINE}/audio/mjMusicPlayer.cpp \
    $${MJENGINE}/audio/mjSoundSource.cpp \
    $${MJENGINE}/core/mjObject.cpp \
    $${MJENGINE}/core/mjVector3.cpp \
    $${MJENGINE}/extLibs/math/mjMathHelper.cpp \
    $${MJENGINE}/extLibs/math/mjMatrixStack.cpp \
    $${MJENGINE}/extLibs/tinyxml/tinyxml2.cpp \
    $${MJENGINE}/extLibs/util/mjMultiPlatform.cpp \
    $${MJENGINE}/extLibs/util/mjXMLHelper.cpp \
    $${MJENGINE}/extLibs/math/Matrix.cpp \
    $${MJENGINE}/graphics/animation/mjAnimation.cpp \
    $${MJENGINE}/graphics/animation/mjAnimationKeyframe.cpp \
    $${MJENGINE}/graphics/animation/mjAnimationSegment.cpp \
    $${MJENGINE}/graphics/animation/mjAnimator.cpp \
    $${MJENGINE}/graphics/animation/mjModelAnimation.cpp \
    $${MJENGINE}/graphics/animation/mjModelPose.cpp \
    $${MJENGINE}/graphics/animation/mjModelStructure.cpp \
    $${MJENGINE}/graphics/animation/mjModelStructureNode.cpp \
    $${MJENGINE}/graphics/mj3rdPersonCamera.cpp \
    $${MJENGINE}/graphics/mjCamera.cpp \
    $${MJENGINE}/graphics/mjDefaultShaders.cpp \
    $${MJENGINE}/graphics/mjImageLoader.cpp \
    $${MJENGINE}/graphics/mjModel.cpp \
    $${MJENGINE}/graphics/mjModelMesh.cpp \
    $${MJENGINE}/graphics/mjSceneGraph.cpp \
    $${MJENGINE}/graphics/mjShader.cpp \
    $${MJENGINE}/graphics/mjSkybox.cpp \
    $${MJENGINE}/graphics/mjSkyboxLevelData.cpp \
    $${MJENGINE}/graphics/mjSkyboxShaders.cpp \
    $${MJENGINE}/physics/mjAABB.cpp \
    $${MJENGINE}/physics/mjCollisionResult.cpp \
    $${MJENGINE}/physics/mjCollisionStructure.cpp \
    $${MJENGINE}/physics/mjCollisionTests.cpp \
    $${MJENGINE}/physics/mjPhysics.cpp \
    $${MJENGINE}/physics/mjPhysicsEffect.cpp \
    $${MJENGINE}/physics/mjSphere.cpp \
    $${MJENGINE}/util/mjModelResource.cpp \
    $${MJENGINE}/util/mjModelStructureResource.cpp \
    $${MJENGINE}/util/mjResource.cpp \
    $${MJENGINE}/util/mjResourceManager.cpp \
    $${MJENGINE}/util/mjSoundResource.cpp \
    $${MJENGINE}/util/mjTextureResource.cpp \
    $${MJENGINE}/graphics/mjAssimpModel.cpp \
    $${MJENGINE}/graphics/renderer/mjRenderer.cpp \
    $${MJENGINE}/graphics/renderer/mjRendererData.cpp \
    $${MJENGINE}/graphics/renderer/mjRendererDataGL.cpp \
    $${MJENGINE}/graphics/renderer/mjRendererGL.cpp \
    $${MJENGINE}/util/mjShaderResource.cpp \
    $${MJENGINE}/input/mjInputEvent.cpp \
    $${MJENGINE}/text/mjTextShaders.cpp \
    $${MJENGINE}/extLibs/utf8-utils/utf8-utils.c \
    $${MJENGINE}/text/mjGraphicCharObject.cpp \
    $${MJENGINE}/util/mjFontResource.cpp \
    $${MJENGINE}/text/mjGraphicText.cpp \
    $${MJENGINE}/util/mjGraphicCharObjectResource.cpp \
    $${MJENGINE}/core/mjGameState.cpp \
    $${MJENGINE}/util/mjFileFromArchive.cpp \
    $${MJENGINE}/internalMessaging/mjInternalMessenger.cpp \
    $${MJENGINE}/internalMessaging/mjInternalMessageReceiver.cpp \
    $${MJENGINE}/graphics/mjMaterialBucket.cpp \
    $${MJENGINE}/util/mjObjectPool.cpp \
    $${MJENGINE}/core/mjTransitionUniverse.cpp \
    $${MJENGINE}/core/mjUniverse.cpp \
    $${MJENGINE}/core/mjUniverseSwitcher.cpp \
    $${MJENGINE}/ui/mjInterfaceBuilder.cpp \
    $${MJENGINE}/ui/mjUIObject.cpp



INCLUDEPATH += $$PWD/../../../sdl/i686-w64-mingw32/include $$PWD/../../../glew/include $$PWD/extLibs/freetype2/include

win32: LIBS += -L$$PWD/../../../glew/lib/Release/Win32/ -L$$PWD/../../../sdl/i686-w64-mingw32/lib/ -L$$PWD/precompiled/freetype2/win32

win32: LIBS += -lmingw32 -mwindows -lSDL2main -lSDL2 -lSDL2_image -lglew32s -lopengl32 -lSDL2_mixer -lfreetype

#linux: LIBS += -lSDL2 -lGL -lGLEW -lSDL2_image -lSDL2_mixer


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += sdl2 glew gl libpng SDL2_image SDL2_mixer assimp freetype2 #for GL3 rendering
#unix: PKGCONFIG += sdl2 glesv2 libpng SDL2_image SDL2_mixer #for GLESv2 rendering
