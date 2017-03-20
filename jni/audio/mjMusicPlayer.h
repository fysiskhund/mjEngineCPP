#ifndef MJMUSICPLAYER_H
#define MJMUSICPLAYER_H

#ifndef OSX
#include <SDL2/SDL_mixer.h>
#else
#include <SDL2_mixer/SDL_mixer.h>
#endif

#include "../extLibs/logger/mjLog.h"
#include "../util/mjSoundResource.h"

namespace mjEngine {


class mjMusicPlayer
{
    public:

        mjMusicPlayer();

        void Load(mjSoundResource* soundRes, int sampleNum);
        void Play();
        void Play(int sampleIndex);
        void SetLoops(int loops);
        void Pause();
        void Resume();
        void Rewind();

        virtual ~mjMusicPlayer();
    protected:
    private:
        int loops = 0;

#ifdef USE_SDL_AUDIO
        Mix_Chunk* currentMusic;
        int channel;
#endif

};

}
#endif // MJMUSICPLAYER_H
