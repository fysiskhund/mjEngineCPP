#ifndef MJMUSICPLAYER_H
#define MJMUSICPLAYER_H

#include "mjSoundSource.h"


#ifdef USE_SDL_AUDIO

#include "sdl/mjMusicPlayer_SDL.h"



#else



namespace mjEngine{

class mjMusicPlayer: public mjSoundSource
{
    public:
        mjMusicPlayer();

        virtual void Load(mjSoundResource* soundRes, int sampleNum) override;
        virtual void Play() override;
        virtual void Play(int sampleIndex) override;
        virtual void Pause() override;
        virtual void Rewind() override;

        virtual ~mjMusicPlayer();
    protected:
    private:
};

}
#endif // USE_SDL_AUDIO

#endif // MJMUSICPLAYER_H
