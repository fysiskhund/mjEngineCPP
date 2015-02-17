#ifndef MJMULTIPLATFORMAUDIO_H
#define MJMULTIPLATFORMAUDIO_H

#ifdef USE_SDL_AUDIO

#include <SDL2/SDL_mixer.h>
#include <vector>



#elif USE_ANDROID_AUDIO

#include <string.h>


#endif // USE_ANDROID_AUDIO



#endif
