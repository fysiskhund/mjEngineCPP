#ifndef MJSOUNDSOURCE_H
#define MJSOUNDSOURCE_H

namespace mjEngine{

class mjSoundSource
{
    public:
        bool loop = false;
        mjSoundSource();


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
