
#include <SDL2/SDL_mixer.h>


namespace mjEngine{

class mjMusicPlayer
{
    public:
        mjMusicPlayer();

        void Load(mjSoundResource* soundRes, int sampleNum);
        void Play();
        void Play(int sampleIndex);
        void Pause();
        void Rewind();

        ~mjMusicPlayer();
    protected:
    private:
        Mix_Music* currentMusic;
        int channel;

};

}
