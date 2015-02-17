
namespace mjEngine{

mjMusicPlayer::mjMusicPlayer()
{
    LOGI("Music player subsystem is Android-JNI bridge");
}

void mjMusicPlayer::Load(mjSoundResource* soundRes, int sampleNum)
{
	std::string cmd = "1:" + soundRes->path;
	//LOGI("loading %s", soundRes->path.c_str());
	mjMultiPlatform::AddCommandForJNI(cmd);

}

void mjMusicPlayer::Play()
{
	std::string cmd = "2:";
	mjMultiPlatform::AddCommandForJNI(cmd);
}
void mjMusicPlayer::Play(int sampleIndex)
{
	Play();
}
void mjMusicPlayer::Pause()
{
	std::string cmd = "3:";
	mjMultiPlatform::AddCommandForJNI(cmd);
}

void mjMusicPlayer::Rewind()
{
	std::string cmd = "4:";
	mjMultiPlatform::AddCommandForJNI(cmd);
}

mjMusicPlayer::~mjMusicPlayer()
{
    //dtor
}

}