#include "mjMusicPlayer.h"

namespace mjEngine{

#ifdef USE_SDL_AUDIO

#include "sdl/mjMusicPlayer_SDL.cpp"



#elseifdef USE_ANDROID_AUDIO

#include "android/mjMusicPlayer_android.cpp"

#else

mjMusicPlayer::mjMusicPlayer()
{
    //ctor
}

void mjMusicPlayer::Load(mjSoundResource* soundRes, int sampleNum)
{

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
