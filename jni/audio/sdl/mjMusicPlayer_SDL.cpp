
mjMusicPlayer::mjMusicPlayer()
{
    Mix_Init(MIX_INIT_OGG);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 512);
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

