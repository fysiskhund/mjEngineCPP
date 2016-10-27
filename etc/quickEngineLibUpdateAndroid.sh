#!/bin/sh
../etc/proToMk.pl mjEngineCPP_asLibrary.pro && cp mjEngineCPP_asLibrary.pro.mk Android.mk && '/common/tools/sdk/ndk-bundle/ndk-build' && cp ../obj/local/armeabi-v7a/libmjEngine.a precompiled/mjEngine/armeabi-v7a/libmjEngine.a && echo "Engine library update completed."
