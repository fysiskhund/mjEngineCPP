

mjMusicPlayer::mjMusicPlayer()
{
    //ctor
}

void mjMusicPlayer::Load(mjSoundResource* soundRes, int sampleNum)
{
	mjMultiPlatform::AddCommandForJNI("1:" + soundRes->path);
}

void mjMusicPlayer::Play()
{
	mjMultiPlatform::AddCommandForJNI("2:");
}
void mjMusicPlayer::Play(int sampleIndex)
{
	Play();
}
void mjMusicPlayer::Pause()
{
	mjMultiPlatform::AddCommandForJNI("3:");
}

void mjMusicPlayer::Rewind()
{
	mjMultiPlatform::AddCommandForJNI("4:");
}

mjMusicPlayer::~mjMusicPlayer()
{
    //dtor
}
