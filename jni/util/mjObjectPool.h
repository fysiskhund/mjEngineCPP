#ifndef MJOBJECTPOOL_H
#define MJOBJECTPOOL_H

#include <vector>
#include "../core/mjObject.h"

namespace mjEngine {


//! Convenience class for easy reuse of mjObjects. Must be subclassed to your
//! particular object by implementing CreateNewObject
class mjObjectPool
{
public:

    mjResourceManager* resourceManager = NULL;

    mjObjectPool();
    ~mjObjectPool();

    //! Initialise the pool so it can work
    void Initialize(mjResourceManager* resourceManager);

    //! Create a bunch of objects and add them to the internal vector
    void AllocateObjects(unsigned howMany);

    //! Get an available object, whether it's new or recycled.
    //! After the object is no longer needed, set the object's isAvailableForPool to true.
    mjObject* GetAvailableObject();


    //! Delete everything from the internal vector, then call clear() in it.
    void Clean();
protected:
    virtual mjObject* CreateNewObject() = 0; // MUST be implemented to your particular mjObject subclass

private:
    std::vector<mjObject*> objects;


};

}
#endif // MJOBJECTPOOL_H
