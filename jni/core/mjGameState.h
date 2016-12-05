#ifndef MJGAMESTATE_H
#define MJGAMESTATE_H


namespace mjEngine {

/*!
 * This class must be sub-classed for each project so mjScenes can pass information among themselves.
 * It is a placeholder class.
 */
class mjGameState
{
public:

    mjGameState();
    virtual bool SaveGameState() = 0;
    virtual bool LoadGameState() = 0;
    virtual ~mjGameState();
};

}


#endif // MJGAMESTATE_H
