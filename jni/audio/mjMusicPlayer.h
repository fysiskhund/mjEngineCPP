#ifndef MJMUSICPLAYER_H
#define MJMUSICPLAYER_H


#include "../extLibs/logger/mjLog.h"
#include "../util/mjSoundResource.h"

#ifdef USE_SDL_AUDIO

#include "sdl/mjMusicPlayer_SDL.txth"



#elif USE_ANDROID_AUDIO

#include "android/mjMusicPlayer_android.txth"

#elif IOS





namespace mjEngine{

class mjMusicPlayer
{
    public:
        int loops = 0;
        mjMusicPlayer();

        void Load(mjSoundResource* soundRes, int sampleNum);
        void Play();
        void Play(int sampleIndex);
        void Pause();
        void Resume();
        void Rewind();

        virtual ~mjMusicPlayer();
    protected:
    private:
};

}
#else

namespace mjEngine{
    
    class mjMusicPlayer
    {
    public:
        int loops = 0;
        
        mjMusicPlayer();
        
        void Load(mjSoundResource* soundRes, int sampleNum);
        void Play();
        void Play(int sampleIndex);
        void Pause();
        void Resume();
        void Rewind();
        
        virtual ~mjMusicPlayer();
    protected:
    private:
    };
    
}

#endif // USE_SDL_AUDIO

#endif // MJMUSICPLAYER_H
