
# Copyright (C) 2014-2017 Alejandro Valenzuela Roca
#
# Only the game will be compiled. The engine will be loaded as a static library.
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

# getting freetype2 into the project
include $(CLEAR_VARS)

LOCAL_MODULE    := freetype2
LOCAL_SRC_FILES := precompiled/freetype2/$(TARGET_ARCH_ABI)/libfreetype.a

include $(PREBUILT_STATIC_LIBRARY)
# -------------

# getting libmjEngine into the project
include $(CLEAR_VARS)

LOCAL_MODULE    := libmjEngine
LOCAL_SRC_FILES := precompiled/mjEngine/$(TARGET_ARCH_ABI)/libmjEngine.a

include $(PREBUILT_STATIC_LIBRARY)
# -------------

# Now, the files from the game are specified:

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(LOCAL_PATH)//extLibs/freetype2/include

LOCAL_MODULE    := libmjGame
LOCAL_SRC_FILES := \
    takkatakkacpp/TakkaTakkaGameState.cpp \
    takkatakkacpp/gameModes/ChallengeGameMode.cpp \
    takkatakkacpp/gameModes/GameMode.cpp \
    takkatakkacpp/gameModes/PartyGameMode.cpp \
    takkatakkacpp/gameObjects/BaitAndSwitchTrackEvent.cpp \
    takkatakkacpp/gameObjects/Bubble.cpp \
    takkatakkacpp/gameObjects/BubbleExplosion.cpp \
    takkatakkacpp/gameObjects/BubbleFragment.cpp \
    takkatakkacpp/gameObjects/BubbleScripts/BaitAndSwitchBubbleScript.cpp \
    takkatakkacpp/gameObjects/BubbleScripts/BaitAndSwitchBubbleScriptSettings.cpp \
    takkatakkacpp/gameObjects/BubbleScripts/BeatZigZagBubbleScript.cpp \
    takkatakkacpp/gameObjects/BubbleScripts/BeatZigZagBubbleScriptSettings.cpp \
    takkatakkacpp/gameObjects/BubbleScripts/BubbleScript.cpp \
    takkatakkacpp/gameObjects/BubbleScripts/BubbleScriptSettings.cpp \
    takkatakkacpp/gameObjects/BubbleScripts/SpiralWalkBubbleScript.cpp \
    takkatakkacpp/gameObjects/BubbleScripts/SpiralWalkBubbleScriptSettings.cpp \
    takkatakkacpp/gameObjects/Choreographer.cpp \
    takkatakkacpp/gameObjects/Draggable.cpp \
    takkatakkacpp/gameObjects/Player.cpp \
    takkatakkacpp/gameObjects/Poke.cpp \
    takkatakkacpp/gameObjects/Step.cpp \
    takkatakkacpp/gameObjects/Track.cpp \
    takkatakkacpp/gameObjects/TrackEvent.cpp \
    takkatakkacpp/gameObjects/TrackLoader.cpp \
    takkatakkacpp/gameObjects/TrackPreview.cpp \
    takkatakkacpp/gl_code.cpp \
    takkatakkacpp/interfaceObjects/HealthBar.cpp \
    takkatakkacpp/interfaceObjects/PictureButton.cpp \
    takkatakkacpp/interfaceObjects/ResponseText.cpp \
    takkatakkacpp/interfaceObjects/ToggleButton.cpp \
    takkatakkacpp/interfaceObjects/TrackSelector.cpp \
    takkatakkacpp/pools/BubbleFragmentPool.cpp \
    takkatakkacpp/shaders/BubbleShaders.cpp \
    takkatakkacpp/subsystems/InterfaceBuilder.cpp \
    takkatakkacpp/subsystems/TokenStore.cpp \
    takkatakkacpp/subsystems/TrackList.cpp \
    takkatakkacpp/subsystems/TrackListLoader.cpp \
    takkatakkacpp/universes/ChooserUniverse.cpp \
    takkatakkacpp/universes/CreditsUniverse.cpp \
    takkatakkacpp/universes/SlideTransitionUniverse.cpp \
    takkatakkacpp/universes/SongUniverse.cpp \
    takkatakkacpp/universes/TitleUniverse.cpp

# -------------

# now, the shared and static libs to be used are specified				   
LOCAL_LDLIBS    := -llog -lGLESv2 -lz -landroid
LOCAL_STATIC_LIBRARIES := libmjEngine png freetype2

# finally we tell ndk-build that the output is a shared library. This will be loaded by Java in the android device
include $(BUILD_SHARED_LIBRARY)
