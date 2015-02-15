


mjSoundSource::mjSoundSource()
{
	LOGI("mjSoundSource subsystem is Android-JNI bridge");
}

void mjSoundSource::Load(mjSoundResource* soundRes, int sampleNumber)
{
	std::string cmd = "51:" + soundRes->path;
		//LOGI("loading %s", soundRes->path.c_str());
		mjMultiPlatform::AddCommandForJNI(cmd);
}

void mjSoundSource::Play(mjVector3& sourceLocation, mjVector3& listenerLocation,
			             mjVector3& listenerDirection, mjVector3& listenerUp, int sampleIndex)
{
	float leftChannel;
	float rightChannel;

	if (CalculateVolumeLevels(sourceLocation, listenerLocation, listenerDirection, listenerUp, &leftChannel, &rightChannel))
	{
		char cmdCharArray[256];
		snprintf(cmdCharArray, 256, "52:%d:%f:%f:%d:%d:%d:%f", sampleIndex, leftChannel, rightChannel, 0, 0, 0, 1.0 );
		std::string cmd = cmdCharArray;
		mjMultiPlatform::AddCommandForJNI(cmd);
	}
}

void mjSoundSource::Play()
{

}
void mjSoundSource::Play(int sampleIndex)
{

}
void mjSoundSource::Pause()
{

}

void mjSoundSource::Rewind()
{

}

mjSoundSource::~mjSoundSource()
{
    //dtor
}

