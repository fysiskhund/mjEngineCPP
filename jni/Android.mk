# Copyright (C) 2016 Alejandro Valenzuela Roca
#
# Compile only the engine. Note: use ndk-build directly, for some reason calling it from Eclipse generates significantly bigger library files. Probably left some debugging flag active!
#
# -------------

# no idea what this does but if you remove it the world ends so better not touch it
# ndk-build works in mysterious ways, whatever
LOCAL_PATH:= $(call my-dir)




# compile the mjEngine, as a library
include $(CLEAR_VARS)


LOCAL_MODULE    := libmjEngine
LOCAL_CFLAGS := -I.

# Now, the file from the engine are specified:
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
    graphics/renderer/mjRendererGL.cpp \
    graphics/renderer/mjRendererData.cpp \
    graphics/renderer/mjRendererDataGL.cpp \
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
    util/mjTextureResource.cpp

# finally we tell ndk-build that the output is a static library. This will be included by Eclipse in the final *.so shared library - see Android.mk.gameOnly
include $(BUILD_STATIC_LIBRARY)
