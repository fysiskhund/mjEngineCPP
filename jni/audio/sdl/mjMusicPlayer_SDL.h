
#include "SDL/SDL_mixer.h"


namespace mjEngine{

class mjMusicPlayer: public mjSoundSource
{
    public:
        mjMusicPlayer();

        virtual void Play() override;
        virtual void Play(int sampleIndex) override;
        virtual void Pause() override;
        virtual void Rewind() override;

        virtual ~mjMusicPlayer();
    protected:
    private:

};

}
