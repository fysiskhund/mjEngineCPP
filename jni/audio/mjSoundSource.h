#ifndef MJSOUNDSOURCE_H
#define MJSOUNDSOURCE_H

#include "../util/mjSoundResource.h"

namespace mjEngine{

class mjSoundSource
{
    public:
        bool loop = false;
        mjSoundSource();

        virtual void Load(mjSoundResource* soundRes, int sampleNumber);
        virtual void Play();
        virtual void Play(int sampleIndex);
        virtual void Pause();
        virtual void Rewind();


        virtual ~mjSoundSource();
    protected:
    private:
};

}

#endif // MJSOUNDSOURCE_H
