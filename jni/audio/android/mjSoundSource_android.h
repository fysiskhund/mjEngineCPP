
namespace mjEngine{

class mjSoundSource
{
    public:
        bool loop = false;
        mjSoundSource();


        void Load(mjSoundResource* soundRes, int sampleNumber);

        void Play(mjVector3& sourceLocation, mjVector3& listenerLocation, int sampleIndex);

        void Play();
        void Play(int sampleIndex);
        void Pause();
        void Rewind();

        float attenuation = 0.05; // Sound sources further than 20m cannot be heard.


        virtual ~mjSoundSource();
    protected:
        bool CalculateVolumeLevels(mjVector3& sourceLocation, mjVector3& listenerLocation, mjVector3& listenerDirection, mjVector3& listenerUp,
        		float* leftChannel, float* rightChannel);

    private:
};

}
