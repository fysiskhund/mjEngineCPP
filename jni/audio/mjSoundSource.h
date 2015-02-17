#ifndef MJSOUNDSOURCE_H
#define MJSOUNDSOURCE_H

#include "../util/mjSoundResource.h"
#include "../core/mjVector3.h"
#include "../extLibs/util/mjMultiPlatformAudio.h"
#include "../graphics/mjCamera.h"





namespace mjEngine{

class mjSoundSource
{
    public:
        bool loop = false;
        float attenuation = 0.05; // Sound sources further than 20m cannot be heard.



        mjSoundSource();


        int Load(mjSoundResource* soundRes, int sampleNumber);

        void Play(mjVector3& sourceLocation, mjVector3& listenerLocation, mjVector3& listenerDirection, mjVector3& listenerUp,
                    int sampleIndex);

        void Play(mjVector3& sourceLocation, int sampleIndex);
        void Play();
        void Play(int sampleIndex);
        void Pause();
        void Rewind();




        virtual ~mjSoundSource();

    protected:
        bool CalculateVolumeLevels(mjVector3& sourceLocation, mjVector3& listenerLocation, mjVector3& listenerDirection, mjVector3& listenerUp,
        		float* leftChannel, float* rightChannel);

#ifdef USE_SDL_AUDIO

#include "sdl/mjSoundSource_SDL.h"



#elif USE_ANDROID_AUDIO

#include "android/mjSoundSource_android.h"

#else

#endif
};

}


#endif // MJSOUNDSOURCE_H
