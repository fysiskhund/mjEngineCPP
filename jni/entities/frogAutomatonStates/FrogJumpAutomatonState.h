#ifndef FROGJUMPAUTOMATONSTATE_H
#define FROGJUMPAUTOMATONSTATE_H


class FrogAutomatonJumpState: Frog::FrogAutomatonState
{
    public:
        FrogAutomatonJumpState(Frog* frog);
        void Enter() override;

    protected:
    private:
};

#endif // FROGJUMPAUTOMATONSTATE_H
