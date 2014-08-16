# Copyright (C) 2014 Alejandro Valenzuela Roca
#
LOCAL_PATH:= $(call my-dir)

# PNG
include $(CLEAR_VARS)

LOCAL_MODULE    := png
LOCAL_SRC_FILES := extLibs/png/libpng.a
#LOCAL_EXPORT_C_INCLUDES := extLibs/png/include

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := mjengine
LOCAL_SRC_FILES := extLibs/tinyxml/tinyxml2.cpp \
				   mjVector3.cpp \
				   graphics/mjCamera.cpp \
				   extLibs/math/Matrix.cpp \
				   graphics/mjImageLoader.cpp \
				   graphics/mjModel.cpp \
				   graphics/mjModelMesh.cpp \
				   graphics/mjDefaultShaders.cpp \
				   graphics/mjShader.cpp \
				   core/mjObject.cpp \
				   gl_code.cpp
				   
LOCAL_LDLIBS    := -llog -lGLESv2 -lz
LOCAL_STATIC_LIBRARIES := png

include $(BUILD_SHARED_LIBRARY)
