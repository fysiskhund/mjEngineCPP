# Copyright (C) 2014 Alejandro Valenzuela Roca
#
LOCAL_PATH:= $(call my-dir)

# PNG
include $(CLEAR_VARS)

LOCAL_MODULE    := png
LOCAL_SRC_FILES := extLibs/png/$(TARGET_ARCH_ABI)/libpng.a
#LOCAL_EXPORT_C_INCLUDES := extLibs/png/include

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_CFLAGS := -I.

LOCAL_MODULE    := mjengine
LOCAL_SRC_FILES := ./audio/mjMusicPlayer.cpp\
				   ./audio/mjSoundSource.cpp\
				   ./physics/mjSphere.cpp\
				   ./physics/mjPhysicsEffect.cpp\
				   ./physics/mjPhysics.cpp\
				   ./physics/mjCollisionTests.cpp\
				   ./physics/mjAABB.cpp\
				   ./physics/mjCollisionResult.cpp\
				   ./graphics/mjDefaultShaders.cpp\
				   ./graphics/mj3rdPersonCamera.cpp\
				   ./graphics/mjModel.cpp\
				   ./graphics/mjSkyboxShaders.cpp\
				   ./graphics/mjShader.cpp\
				   ./graphics/mjCamera.cpp\
				   ./graphics/mjSkybox.cpp\
				   ./graphics/mjSkyboxLevelData.cpp\
				   ./graphics/mjModelMesh.cpp\
				   ./graphics/mjSceneGraph.cpp\
				   ./graphics/animation/mjModelPose.cpp\
				   ./graphics/animation/mjAnimationKeyframe.cpp\
				   ./graphics/animation/mjAnimator.cpp\
				   ./graphics/animation/mjModelStructure.cpp\
				   ./graphics/animation/mjAnimation.cpp\
				   ./graphics/animation/mjModelAnimation.cpp\
				   ./graphics/animation/mjAnimationSegment.cpp\
				   ./graphics/mjImageLoader.cpp\
				   ./game/entities/BatMaton.cpp\
				   ./game/entities/Character.cpp\
				   ./game/entities/Frog.cpp\
				   ./game/entities/BatBot.cpp\
				   ./game/entities/Bird.cpp\
				   ./game/entities/Plant.cpp\
				   ./game/entities/GlowBeing.cpp\
				   ./game/entities/frogAutomatonStates/FrogJumpAutomatonState.cpp\
				   ./game/entities/frogAutomatonStates/FrogAutomatonStopState.cpp\
				   ./game/entities/batMatonStates/DetectBatMatonState.cpp\
				   ./game/entities/batMatonStates/AttackBatMatonState.cpp\
				   ./game/entities/batMatonStates/WanderBatMatonState.cpp\
				   ./extLibs/math/mjMatrixStack.cpp\
				   ./extLibs/math/Matrix.cpp\
				   ./extLibs/math/mjMathHelper.cpp\
				   ./extLibs/tinyxml/tinyxml2.cpp\
				   ./extLibs/util/mjMultiPlatform.cpp\
				   ./extLibs/util/mjXMLHelper.cpp\
				   ./util/mjModelStructureResource.cpp\
				   ./util/mjModelResource.cpp\
				   ./util/mjResourceManager.cpp\
				   ./util/mjTextureResource.cpp\
				   ./util/mjResource.cpp\
				   ./util/mjSoundResource.cpp\
				   ./game/ambient/DustDevil.cpp\
				   ./game/Ambient.cpp\
				   ./game/windStates/WindState.cpp\
				   ./game/windStates/SteadyDirectionState.cpp\
				   ./game/windStates/DustDevilState.cpp\
				   ./game/TerrainCreator.cpp\
				   ./game/Level.cpp\
				   ./game/PlatformUniverseScene.cpp\
				   ./game/gl_code.cpp\
				   ./game/EntityCreator.cpp\
				   ./ai/mjAutomaton.cpp\
				   ./ai/mjAutomatonState.cpp\
				   ./game/terrainTypes/Box.cpp\
				   ./game/terrainTypes/FallingBox.cpp\
				   ./core/mjObject.cpp\
				   ./core/mjScene.cpp\
				   ./core/mjSceneManager.cpp\
				   ./core/mjVector3.cpp
				   
LOCAL_LDLIBS    := -llog -lGLESv2 -lz
LOCAL_STATIC_LIBRARIES := png

include $(BUILD_SHARED_LIBRARY)
