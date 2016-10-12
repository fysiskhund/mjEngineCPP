
#ifndef MJLOG_H
#define MJLOG_H

#ifdef ANDROID

#include <android/log.h>
#define  LOG_TAG    "mj"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#endif
#if defined(DESKTOP_SDL) || defined(IOS)

#include <stdio.h>

#define LOGI(...) printf(__VA_ARGS__); printf("\n");

#endif

#endif
/*namespace mjEngine{

class mjLog{
public:
	static void I(const char* format, ...);

};
}
*/

