#include "mjSoundSource.h"


namespace mjEngine{

void mjSoundSource::Play(mjVector3& sourceLocation, int sampleIndex)
{
    if (mjCamera::currentCamera)
    {
        Play(sourceLocation, mjCamera::currentCamera->pos, mjCamera::currentCamera->dir,
             mjCamera::currentCamera->up, sampleIndex);
    } else{
        LOGI("mjCamera::CurrentCamera has not been set, cannot play positional audio effect.");
    }
}

bool mjSoundSource::CalculateVolumeLevels(mjVector3& sourceLocation, mjVector3& listenerLocation, mjVector3& listenerDirection, mjVector3& listenerUp,
		float* leftChannel, float* rightChannel){

	mjVector3 sourceToListener;
	float distance;
	float attenuationDueToDistance;

	sourceToListener.CopyFrom(sourceLocation);
	sourceToListener.Subtract(listenerLocation);

	distance = sourceToListener.GetNorm();




	attenuationDueToDistance = 1.0-(distance*attenuation);

	if (attenuationDueToDistance <= 0)
	{
		return false; // Sound source is too far away. Nothing is emitted.
	} else
	{
		mjVector3 leftVector;

        listenerUp.CrossOut(listenerDirection, &leftVector);
        //leftVector.MulScalar(1.0/attenuation);
        // Get scalar component of the sourceToListener vector on leftVector
        float scalarComponentForSound = leftVector.Dot(sourceToListener);

        // Scale the component so that it is maximum 1.0?
        scalarComponentForSound *= attenuation;


        *leftChannel = (0.5*scalarComponentForSound) + 0.5;
        *rightChannel = 1.0 - *leftChannel;

        *leftChannel *= attenuationDueToDistance;
        *rightChannel *= attenuationDueToDistance;

		return true;
	}
}


#ifdef USE_SDL_AUDIO

#include "sdl/mjSoundSource_SDL.txtcpp"



#elif USE_ANDROID_AUDIO

#include "android/mjSoundSource_android.txtcpp"

#else




mjSoundSource::mjSoundSource()
{
    LOGI("Fake SoundSource created. Check the USE_SDL_AUDIO or USE_ANDROID_AUDIO compilation variables are set to ensure that the proper version of mjSoundSource is compiled in")
}

int mjSoundSource::Load(mjSoundResource* soundRes, int sampleNumber)
{
    return 0;
}

void mjSoundSource::Play(mjEngine::mjVector3&, mjEngine::mjVector3&, mjEngine::mjVector3&, mjEngine::mjVector3&, int)
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
