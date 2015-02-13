

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

        float attenuation = 0.0025; // Sound sources further than 20m cannot be heard.

        virtual ~mjSoundSource();
    protected:
    private:
};

}
