# Copyright (C) 2014-2016 Alejandro Valenzuela Roca
#
# "GAME ONLY" which means the precompiled mjEngine will be used instead of compiling EVERYTHING
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



# getting libmjEngine into the project
include $(CLEAR_VARS)

LOCAL_MODULE    := libmjEngine
LOCAL_SRC_FILES := precompiled/mjEngine/$(TARGET_ARCH_ABI)/libmjEngine.a

include $(PREBUILT_STATIC_LIBRARY)
# -------------



# Now, the files from the actual game project are specified:

include $(CLEAR_VARS)

LOCAL_CFLAGS := -I.

LOCAL_MODULE    := libmjGame
LOCAL_SRC_FILES := game/Ambient.cpp \
    game/EntityCreator.cpp \
    game/gl_code.cpp \
    game/Level.cpp \
    game/PlatformUniverseScene.cpp \
    game/TerrainCreator.cpp \
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
    game/entities/KosmoObject.cpp \
    game/entities/FrogBoss.cpp \
    game/entities/frogBossAutomatonStates/FrogBossAutomatonHuntState.cpp \
    game/entities/frogBossAutomatonStates/FrogBossAutomatonSlamState.cpp \
    game/entities/frogBossAutomatonStates/FrogBossAutomatonWaitForLandingState.cpp \
    game/terrainTypes/TriggerBox.cpp \
    game/entities/Baobab.cpp
# -------------

# now, the shared and static libs to be used are specified				   
LOCAL_LDLIBS    := -llog -lGLESv2 -lz
LOCAL_STATIC_LIBRARIES := libmjEngine png

# finally we tell ndk-build that the output is a shared library. This will be loaded by Java in the android device
include $(BUILD_SHARED_LIBRARY)
