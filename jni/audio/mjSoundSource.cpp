#include "mjSoundSource.h"


namespace mjEngine{

void mjSoundSource::Play(mjVector3& sourceLocation, int sampleIndex)
{
    if (mjCamera::currentCamera)
    {
        Play(sourceLocation, mjCamera::currentCamera->pos, mjCamera::currentCamera->dir,
             mjCamera::currentCamera->up, sampleIndex);
    } else{
        LOGI("mjCamera::CurrentCamera has not been set, cannot play positional audio effect.")
    }
}

bool mjSoundSource::CalculateVolumeLevels(mjVector3& sourceLocation, mjVector3& listenerLocation, mjVector3& listenerDirection, mjVector3& listenerUp,
		float* leftChannel, float* rightChannel){

	mjVector3 sourceToListener;
	float distance;
	float attenuationDueToDistance;

	sourceToListener.CopyFrom(listenerLocation);
	sourceToListener.Subtract(sourceLocation);

	distance = sourceToListener.Normalize();

	attenuationDueToDistance = 1.0-(distance*attenuation);

	if (attenuationDueToDistance <= 0)
	{
		return false; // Sound source is too far away. Nothing is emitted.
	} else
	{
		float cosTheta = sourceToListener.Dot(listenerDirection);

        *leftChannel = 0.5;
		//*leftChannel = cosTheta*attenuationDueToDistance;

		*rightChannel = (1.0-cosTheta)*attenuationDueToDistance;

		return true;
	}
}


#ifdef USE_SDL_AUDIO

#include "sdl/mjSoundSource_SDL.cpp"



#elif USE_ANDROID_AUDIO

#include "android/mjSoundSource_android.cpp"

#else




mjSoundSource::mjSoundSource()
{
    LOGI("Fake SoundSource created. Check the USE_SDL_AUDIO or USE_ANDROID_AUDIO compilation variables are set to ensure that the proper version of mjSoundSource is compiled in")
}

void mjSoundSource::Load(mjSoundResource* soundRes, int sampleNumber)
{

}

void mjSoundSource::Play(mjVector3& sourceLocation, mjVector3& listenerLocation, int sampleIndex)
{

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


#endif
}
