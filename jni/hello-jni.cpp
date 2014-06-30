/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#include <stdio.h>

#include "mjVector3.h"
#include "graphics/mjModel.h"


#define BUFSIZ 1024

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/hellojni/HelloJni.java
 */
using namespace mjEngine;

extern "C"{

JNIEXPORT jstring JNICALL
Java_co_phong_mjengine_HelloJni_stringFromJNI( JNIEnv* env,
                                                  jobject thiz )
{
#if defined(__arm__)
  #if defined(__ARM_ARCH_7A__)
    #if defined(__ARM_NEON__)
      #define ABI "armeabi-v7a/NEON"
    #else
      #define ABI "armeabi-v7a"
    #endif
  #else
   #define ABI "armeabi"
  #endif
#elif defined(__i386__)
   #define ABI "x86"
#elif defined(__mips__)
   #define ABI "mips"
#else
   #define ABI "unknown"
#endif
	
	mjVector3* r = new mjVector3(1,2,3);
	mjVector3* q = new mjVector3(4,5,6);

    mjModel* model = new mjModel();
    model->LoadFromFile("/sdcard/mjEngineCPP/sprite.mesh.xml");


    if (model->status[0] == NULL)
    {
	
	model->status[0] = 'o';
	model->status[1] = 'k';
	model->status[2] = '.';
	model->status[3] = NULL;
    }




    return env->NewStringUTF( model->status);
	delete r;
	delete q;
}


}
