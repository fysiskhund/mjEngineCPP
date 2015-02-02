
mjMusicPlayer::mjMusicPlayer()
{
    Mix_Init(MIX_INIT_OGG);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 512);
    currentMusic = NULL;
}

void mjMusicPlayer::Load(mjSoundResource* soundRes, int sampleNumber)
{
   currentMusic = Mix_LoadMUS(soundRes->path.c_str());
}

void mjMusicPlayer::Play()
{
    if (currentMusic)
    {
        channel = Mix_PlayMusic(currentMusic, -1);
    }
}
void mjMusicPlayer::Play(int sampleIndex)
{
    Play();
}
void mjMusicPlayer::Pause()
{
    Mix_Pause(channel);
}

void mjMusicPlayer::Rewind()
{
    Mix_RewindMusic();
}

mjMusicPlayer::~mjMusicPlayer()
{
    //dtor
}

