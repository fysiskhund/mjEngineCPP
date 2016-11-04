#ifndef MJRESOURCE_H
#define MJRESOURCE_H

#include <string>

namespace mjEngine {

class mjResource
{
    public:
        std::string path;
        unsigned long identifier = 0; // For quick lookups, when possible.
        int modifier = 0;
    protected:
    private:
};

}

#endif // MJRESOURCE_H
