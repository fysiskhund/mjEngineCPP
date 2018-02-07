#include "mjMusicPlayer.h"



#ifdef USE_SDL_AUDIO

#include "sdl/mjMusicPlayer_SDL.txtcpp"


#elif USE_ANDROID_AUDIO

#include "android/mjMusicPlayer_android.txtcpp"

#elif IOS

// Note: in XCode this file is marked as Objective-C++ source to enable [NSStuff functionsAndEtc];

#include <Foundation/Foundation.h>
#include <Foundation/NSString.h>

#include <AVFoundation/AVFoundation.h>
#include <AudioToolbox/AudioToolbox.h>
AVAudioPlayer* player;


//@property (nonatomic, retain) AVAudioPlayer *myAudioPlayer;


namespace mjEngine{
    
    mjMusicPlayer::mjMusicPlayer()
    {
        LOGI("iOS mjMusicPlayer in use.");
        
        
    }
    
    void mjMusicPlayer::Load(mjSoundResource* soundRes, int sampleNum)
    {
        
        NSString* iosPath = [NSString stringWithUTF8String:soundRes->path.c_str()];
        
        NSURL* fileURL = [[NSURL alloc] initFileURLWithPath:iosPath];
        
        player = [[AVAudioPlayer alloc] initWithContentsOfURL:fileURL error:nil];
        [player stop];
        player.numberOfLoops = loops;
    }
    
    void mjMusicPlayer::Play()
    {
        [player play];
    }
    void mjMusicPlayer::Play(int sampleIndex)
    {
        Play(); // FIXME: for now ignore sampleIndex
    }
    void mjMusicPlayer::SetLoops(int loops)
    {
        this->loops = loops;
        player.numberOfLoops = loops;
    }
    void mjMusicPlayer::Pause()
    {
        [player pause];
    }
    
    void mjMusicPlayer::Rewind()
    {
        player.currentTime = 0;
    }
    
    mjMusicPlayer::~mjMusicPlayer()
    {
        //dtor
    }
    void mjMusicPlayer::Resume()
    {
        [player play];
    }
    
}

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
void mjMusicPlayer::SetLoops(int loops)
{
    this->loops = loops;
}
void mjMusicPlayer::Pause()
{

}

void mjMusicPlayer::Rewind()
{

}


void mjMusicPlayer::Free()
{
    // Nothing! But in platforms that need it, free the channel!

}

mjMusicPlayer::~mjMusicPlayer()
{
    //dtor
    Free();
}

}
#endif // not USE_SDL_AUDIO



