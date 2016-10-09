# Copyright (C) 2014-2016 Alejandro Valenzuela Roca
#
# EVERYTHING will be compiled. This is more of a sanity test for the system since it takes a significant amount of time to be done
#
# -------------

# no idea what this does but if you remove it the world ends so better not touch it
# ndk-build works in mysterious ways, whatever
LOCAL_PATH:= $(call my-dir)




# getting libPNG into the project
include $(CLEAR_VARS)

LOCAL_MODULE    := png
LOCAL_SRC_FILES := precompiled/png/$(TARGET_ARCH_ABI)/libpng.a

include $(PREBUILT_STATIC_LIBRARY)
# -------------



# Now, the files from both the engine and the game project are specified:

include $(CLEAR_VARS)

LOCAL_CFLAGS := -I.

LOCAL_MODULE    := libmjGame
LOCAL_SRC_FILES := ai/mjAutomaton.cpp \
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
    graphics/renderer/mjRenderer.cpp \
    graphics/renderer/mjRendererData.cpp \
    graphics/renderer/mjRendererGL.cpp \
    graphics/renderer/mjRendererDataGL.cpp \
    graphics/mjSceneGraph.cpp \
    graphics/mjShader.cpp \
    graphics/mjSkybox.cpp \
    graphics/mjSkyboxLevelData.cpp \
    graphics/mjSkyboxShaders.cpp \
    graphics/mjAssimpModel.cpp \
    input/mjInputEvent.cpp \
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
    util/mjShaderResource.cpp \
    util/mjSoundResource.cpp \
    util/mjTextureResource.cpp \
   takkatakkacpp/gameObjects/Bubble.cpp \
	takkatakkacpp/gameObjects/Track.cpp \
	takkatakkacpp/gameObjects/Step.cpp \
	takkatakkacpp/gameObjects/Poke.cpp \
	takkatakkacpp/gameObjects/TrackLoader.cpp \
	takkatakkacpp/gameObjects/BubbleScripts/BubbleScript.cpp \
	takkatakkacpp/gameObjects/BubbleScripts/BubbleScriptSettings.cpp \
	takkatakkacpp/gameObjects/BubbleScripts/SpiralWalkBubbleScriptSettings.cpp \
	takkatakkacpp/gameObjects/BubbleScripts/SpiralWalkBubbleScript.cpp \
	takkatakkacpp/TitleUniverse.cpp \
	takkatakkacpp/gl_code.cpp \
	takkatakkacpp/SongUniverse.cpp
# -------------

# now, the shared and static libs to be used are specified		   
LOCAL_LDLIBS    := -llog -lGLESv2 -lz
LOCAL_STATIC_LIBRARIES := png

# finally we tell ndk-build that the output is a shared library (libmjGame.so) . This will be loaded by Java in the android device
include $(BUILD_SHARED_LIBRARY)
