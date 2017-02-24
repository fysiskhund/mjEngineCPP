#ifndef MJINTERNALMESSENGER_H
#define MJINTERNALMESSENGER_H

#include <vector>

#include "mjInternalMessageReceiver.h"
#include "extLibs/logger/mjLog.h"

namespace mjEngine {

#define INTERNAL_MESSENGER_ALL_RECIPIENTS 0

typedef struct {
    unsigned int categoryID;
    std::vector<mjInternalMessageReceiver* > subscribers;
} subscriberCategory;

class mjInternalMessenger
{
public:
    //! Initialises the categories list
    mjInternalMessenger();
    //! Put the subscriber in category lists and link its CastMessage
    void Subscribe(mjInternalMessageReceiver* subscriber, unsigned int* recipientCategories = nullptr);
    bool CastMessage(void* sender, void* contents, unsigned int type, unsigned int intendedRecipients = INTERNAL_MESSENGER_ALL_RECIPIENTS);
    bool Unsubscribe(mjInternalMessageReceiver* subscriber);
private:

    static bool internalCastMessage(void* sender, void* contents, unsigned int type, unsigned int intendedRecipientsALL_RECIPIENTS);
    static std::vector<subscriberCategory* > categories;
    static subscriberCategory* GetCategory(unsigned int categoryID, bool createIfNotFound = false);
    static void internalSubscribe(mjInternalMessageReceiver* subscriber, unsigned int* recipientCategories);
    static bool internalUnsubscribe(mjInternalMessageReceiver* subscriber);
};

}
#endif // MJINTERNALMESSENGER_H
