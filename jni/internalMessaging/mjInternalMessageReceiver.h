#ifndef MJINTERNALMESSAGERECEIVER_H
#define MJINTERNALMESSAGERECEIVER_H

namespace mjEngine {



class mjInternalMessageReceiver
{
public:
    virtual void ReceiveInternalMessage(void* contents, unsigned int type, void* sender) = 0;
    static bool NoCrash(void* sender, void* contents, unsigned int type, unsigned int intendedRecipients);
    bool (*CastMessage)(void* sender, void* contents, unsigned int type, unsigned int intendedRecipients) = NoCrash;
private:

};

}

#endif // MJINTERNALMESSAGERECEIVER_H
