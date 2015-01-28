#include "mjMusicPlayer.h"

namespace mjEngine{

#ifdef USE_SDL_AUDIO

#include "sdl/mjMusicPlayer_SDL.cpp"



#else

mjMusicPlayer::mjMusicPlayer()
{
    //ctor
}

void mjMusicPlayer::Play()
{

}
void mjMusicPlayer::Play(int sampleIndex)
{

}
void mjMusicPlayer::Pause()
{

}

void mjMusicPlayer::Rewind()
{

}

mjMusicPlayer::~mjMusicPlayer()
{
    //dtor
}

#endif // not USE_SDL_AUDIO
}
