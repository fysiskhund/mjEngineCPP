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

LOCAL_MODULE    := mjengine
LOCAL_SRC_FILES := extLibs/tinyxml/tinyxml2.cpp \
				   extLibs/util/mjMultiPlatform.cpp \
				   ai/mjAutomaton.cpp \
				   ai/mjAutomatonState.cpp \
				   core/mjVector3.cpp \
				   core/mjScene.cpp \
				   graphics/mjCamera.cpp \
				   graphics/mj3rdPersonCamera.cpp \
				   extLibs/math/Matrix.cpp \
				   extLibs/math/mjMathHelper.cpp \
				   extLibs/util/mjXMLHelper.cpp \
				   util/mjResourceManager.cpp \
				   util/mjResource.cpp \
				   util/mjModelResource.cpp \
				   util/mjTextureResource.cpp \
				   graphics/mjImageLoader.cpp \
				   graphics/mjModel.cpp \
				   graphics/animation/mjModelPose.cpp \
				   graphics/animation/mjModelAnimation.cpp \
				   graphics/mjModelMesh.cpp \
				   graphics/mjSkyboxLevelData.cpp \
				   graphics/mjDefaultShaders.cpp \
				   graphics/mjSkyboxShaders.cpp \
				   graphics/mjSkybox.cpp \
				   graphics/mjShader.cpp \
				   graphics/mjSceneGraph.cpp \
				   physics/mjPhysics.cpp \
				   physics/mjSphere.cpp \
				   physics/mjAABB.cpp \
				   physics/mjCollisionResult.cpp \
				   physics/mjCollisionTests.cpp \
				   physics/mjPhysicsEffect.cpp \
				   core/mjObject.cpp \
				   entities/Character.cpp \
				   entities/Bird.cpp \
				   entities/BatBot.cpp \
				   entities/BatMaton.cpp \
				   entities/BatMatonState.cpp \
				   entities/batMatonStates/WanderBatMatonState.cpp \
				   entities/Plant.cpp \
				   entities/GlowBeing.cpp \
				   terrainTypes/Box.cpp \
				   game/Level.cpp \
				   game/TerrainCreator.cpp \
				   game/EntityCreator.cpp \
				   game/PlatformUniverseScene.cpp \
				   game/Ambient.cpp \
				   game/windStates/WindState.cpp \
				   game/windStates/SteadyDirectionState.cpp \
				   game/windStates/DustDevilState.cpp \
				   game/ambient/DustDevil.cpp \
				   game/gl_code.cpp
				   
LOCAL_LDLIBS    := -llog -lGLESv2 -lz
LOCAL_STATIC_LIBRARIES := png

include $(BUILD_SHARED_LIBRARY)
