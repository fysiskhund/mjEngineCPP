#include "mjInternalMessenger.h"

namespace mjEngine {

std::vector<subscriberCategory* > mjInternalMessenger::categories;

mjInternalMessenger::mjInternalMessenger()
{
    if (categories.size() == 0)
    {
        subscriberCategory* newCat = new subscriberCategory();
        newCat->categoryID = INTERNAL_MESSENGER_ALL_RECIPIENTS;
        categories.push_back(newCat);
    }
}

void mjInternalMessenger::Subscribe(mjInternalMessageReceiver* subscriber, unsigned int* recipientCategories)
{
    internalSubscribe(subscriber, recipientCategories);
}

bool mjInternalMessenger::CastMessage(void* sender, void* contents, unsigned int type, unsigned int intendedRecipients)
{
    return internalCastMessage(sender, contents, type, intendedRecipients);
}

bool mjInternalMessenger::Unsubscribe(mjInternalMessageReceiver* subscriber)
{
    return internalUnsubscribe(subscriber);
}


void mjInternalMessenger::internalSubscribe(mjInternalMessageReceiver* subscriber, unsigned int* recipientCategories)
{
    subscriberCategory* category;

    if (recipientCategories)
    {
        int i = 0;
        while (recipientCategories[i]) {
            category = GetCategory(recipientCategories[i], false);
            category->subscribers.push_back(subscriber);

            i++;
        }
    }

    // Always add to category INTERNAL_MESSENGER_ALL_RECIPIENTS aka 0
    categories[0]->subscribers.push_back(subscriber);

    subscriber->CastMessage = &internalCastMessage;
}


bool mjInternalMessenger::internalCastMessage(void* sender, void* contents, unsigned int type, unsigned int intendedRecipients)
{
    subscriberCategory* recipients;

    if (intendedRecipients)
    {
        recipients = GetCategory(intendedRecipients, false);
    } else
    {
        recipients = categories[0];
    }

    if (recipients)
    {
        std::vector<mjInternalMessageReceiver* >* subscribers = &recipients->subscribers;

        unsigned int last = subscribers->size();
        for( unsigned int i = 0; i < last; i++)
        {
            if ((void*) (*subscribers)[i] != sender)
            {
                //LOGI("Sending message to 0x%x", (*subscribers)[i]);
                (*subscribers)[i]->ReceiveInternalMessage(contents, type, sender);
            }
        }
        return true;
    } else
    {
        return false;
    }
}

subscriberCategory* mjInternalMessenger::GetCategory(unsigned int categoryID, bool createIfNotFound)
{
    for (unsigned int i = 1; i < categories.size(); i++)
    {
        if (categories[i]->categoryID == categoryID)
        {
            return categories[i];
        }
    }

    if (createIfNotFound)
    {
        subscriberCategory* newCat = new subscriberCategory();
        newCat->categoryID = categoryID;
        categories.push_back(newCat);
        return newCat;
    } else
    {
        return nullptr;
    }
}

bool mjInternalMessenger::internalUnsubscribe(mjInternalMessageReceiver* subscriber)
{
    bool result = false;
    for (unsigned int i = 0; i < categories.size(); i++)
    {
        subscriberCategory* category = categories[i];
        std::vector<mjInternalMessageReceiver*>::iterator catIt;
        std::vector<mjInternalMessageReceiver*>::iterator catLast = category->subscribers.end();

        for (catIt = category->subscribers.begin(); catIt != catLast ; catIt++)
        {
            if (subscriber == *catIt)
            {
                if (i == 0 )
                {
                    subscriber->CastMessage = subscriber->NoCrash; // re-link the CastMessage method to its internal
                                                               // "NoCrash" method to avoid crashes
                }
                //LOGI("Erasing subscriber 0x%x", subscriber);
                catIt = category->subscribers.erase(catIt);

                result = true;
                break;
            }
        }
    }
    return result;
}

}
