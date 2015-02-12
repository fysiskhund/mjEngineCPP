#ifndef MJSOUNDSOURCE_H
#define MJSOUNDSOURCE_H

#include "../util/mjSoundResource.h"
#include "../core/mjVector3.h"


#ifdef USE_SDL_AUDIO

#include "sdl/mjSoundSource_SDL.h"



#elif USE_ANDROID_AUDIO

#include "android/mjSoundSource_android.h"

#else


namespace mjEngine{

class mjSoundSource
{
    public:
        bool loop = false;
        mjSoundSource();


        void Load(mjSoundResource* soundRes, int sampleNumber);

        void Play(mjVector3& sourceLocation, mjVector3& listenerLocation, int sampleIndex);

        void Play();
        void Play(int sampleIndex);
        void Pause();
        void Rewind();

        float attenuation;


        virtual ~mjSoundSource();
    protected:
        bool CalculateVolumes(mjVector3& sourceLocation, mjVector3& listenerLocation, float* leftChannel, float* rightChannel);

    private:
};

}
#endif

#endif // MJSOUNDSOURCE_H
