APP_STL := gnustl_static

APP_ABI := armeabi-v7a #x86
APP_PLATFORM := android-19


NDK_TOOLCHAIN_VERSION := clang
APP_CPPFLAGS += -std=c++11 -DUSE_GLES2 -DUSE_LIBPNG -DUSE_ANDROID_AUDIO -IextLibs/freetype2/include
