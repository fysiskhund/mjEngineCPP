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
				   core/mjVector3.cpp \
				   graphics/mjCamera.cpp \
				   graphics/mj3rdPersonCamera.cpp \
				   extLibs/math/Matrix.cpp \
				   extLibs/math/mjMathHelper.cpp \
				   graphics/mjImageLoader.cpp \
				   graphics/mjModel.cpp \
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
				   terrainTypes/Box.cpp \
				   game/Level.cpp \
				   game/TerrainCreator.cpp \
				   game/EntityCreator.cpp \
				   game/gl_code.cpp
				   
LOCAL_LDLIBS    := -llog -lGLESv2 -lz
LOCAL_STATIC_LIBRARIES := png

include $(BUILD_SHARED_LIBRARY)
