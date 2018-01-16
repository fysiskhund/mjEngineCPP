#ifndef MJAUTOMATONSTATE_H
#define MJAUTOMATONSTATE_H

namespace mjEngine {

class mjAutomatonState
{
    public:



        mjAutomatonState();
        ~mjAutomatonState();

               float maxTime = -1;
        float accumulatedTime = 0;

        int destStateOnTimeExpiration = -1;

        virtual void Enter();

        virtual void Execute(double t_elapsed);
        virtual void Update(double t_elapsed);

        virtual void Reset();

        virtual void Leave();
        void SwitchToState(int destState);
        int switchToStateNow = -1;
    protected:
    private:

};

}
#endif // MJAUTOMATONSTATE_H
