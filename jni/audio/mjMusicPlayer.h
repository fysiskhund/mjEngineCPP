#ifndef MJMUSICPLAYER_H
#define MJMUSICPLAYER_H

#include "mjSoundSource.h"

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
#endif // MJMUSICPLAYER_H
