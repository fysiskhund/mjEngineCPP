


mjSoundSource::mjSoundSource()
{
    //ctor
}

void mjSoundSource::Load(mjSoundResource* soundRes, int sampleNumber)
{
    samples.push_back(Mix_LoadWAV(soundRes->path.c_str()));
}

void mjSoundSource::Play(mjVector3& sourceLocation, mjVector3& listenerLocation, mjVector3& listenerDirection, mjVector3& listenerUp, int sampleIndex)
{
    float leftChannel;
    float rightChannel;

    if (CalculateVolumeLevels(sourceLocation, listenerLocation, listenerDirection, listenerUp, &leftChannel, &rightChannel))
    {
        leftChannel *= 127;
        int playingChannel = Mix_PlayChannel(-1, samples[sampleIndex], 0);
        Mix_SetPanning(playingChannel, leftChannel, 254-leftChannel);
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

