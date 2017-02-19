#include "mjInternalMessageReceiver.h"

namespace mjEngine {


bool mjInternalMessageReceiver::NoCrash(void *sender, void *contents, unsigned int type, unsigned int intendedRecipients)
{
    // Nothing, just don't crash if not connected pl0x
    //LOGI("Message from 0x%x not sent, because it's not subscribed to the mjInternalMessenger", sender);

    return false; // Message not sent because we're not subscribed to anything!
}


}
