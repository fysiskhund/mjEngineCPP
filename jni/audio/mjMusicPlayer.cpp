#include "mjMusicPlayer.h"



#ifdef USE_SDL_AUDIO

#include "sdl/mjMusicPlayer_SDL.txtcpp"


#elif USE_ANDROID_AUDIO

#include "android/mjMusicPlayer_android.txtcpp"

#else



namespace mjEngine{

mjMusicPlayer::mjMusicPlayer()
{
    LOGI("Fake mjMusicPlayer in use. No music will be played. Check compilation switches to enable the proper audio system for the platform");
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

}
#endif // not USE_SDL_AUDIO

