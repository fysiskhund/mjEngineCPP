

namespace mjEngine{

class mjSoundSource
{
    public:
        bool loop = false;
        mjSoundSource();


        void Load(mjSoundResource* soundRes, int sampleNumber);

        void Play(mjVector3& soundLocation, int sampleIndex);

        void Play();
        void Play(int sampleIndex);
        void Pause();
        void Rewind();

        float attenuation;

        virtual ~mjSoundSource();
    protected:
    private:
};

}
