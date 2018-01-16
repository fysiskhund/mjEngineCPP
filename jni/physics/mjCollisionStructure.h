#ifndef MJCOLLISIONSTRUCTURE_H
#define MJCOLLISIONSTRUCTURE_H

#include <vector>

#include "../core/mjObject.h"


namespace mjEngine{


class mjCollisionStructure
{
    public:

        std::vector<mjObject*> objects;
        unsigned numDivisions = 4;

        mjCollisionStructure();
        virtual void AddObject(mjObject* obj);
        virtual void CreateBoundaries();
        virtual void Update(double t_elapsed);


        virtual ~mjCollisionStructure();
    protected:
        float bounds[6] = {  OVER_9000,  OVER_9000,  OVER_9000,
                            -OVER_9000, -OVER_9000, -OVER_9000};
    private:
};

}
#endif // MJCOLLISIONSTRUCTURE_H
