
#ifdef ANDROID

#include <android/log.h>
#define  LOG_TAG    "mj"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#endif
/*namespace mjEngine{

class mjLog{
public:
	static void I(const char* format, ...);

};
}
*/

