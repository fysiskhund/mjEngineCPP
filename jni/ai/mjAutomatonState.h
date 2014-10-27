#ifndef MJAUTOMATONSTATE_H
#define MJAUTOMATONSTATE_H

namespace mjEngine {

class mjAutomatonState
{
    public:



        mjAutomatonState();
        ~mjAutomatonState();

               float maxTime = 0;
        float accumulatedTime = 0;

        int destStateOnTimeExpiration = -1;

        virtual void Enter();

        virtual void Execute(float t_elapsed);
        virtual void Update(float t_elapsed);

        virtual void Reset();

        virtual void Leave();
    protected:
    private:
};

}
#endif // MJAUTOMATONSTATE_H
