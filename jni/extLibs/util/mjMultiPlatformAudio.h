#ifndef MJMULTIPLATFORMAUDIO_H
#define MJMULTIPLATFORMAUDIO_H

#ifdef USE_SDL_AUDIO

#ifndef OSX
#include <SDL2/SDL_mixer.h>
#else
#include <SDL2_mixer/SDL_mixer.h>
#endif
#include <vector>



#elif USE_ANDROID_AUDIO

#include <string.h>


#endif // USE_ANDROID_AUDIO



#endif
