#ifndef MJMATRIXSTACK_H
#define MJMATRIXSTACK_H

#include "Matrix.h"

namespace mjEngine {

class mjMatrixStack
{
    public:
        float ** mStack;
        float * current;
        unsigned currentIndex = 0;
        unsigned maxSize = 15;
        mjMatrixStack();
        mjMatrixStack(unsigned size);
        ~mjMatrixStack();
        void Push(float* m);

        // Add a level to the stack and copy the specified matrix there, without multiplying
        void Insert(float* m);
        void Pop();
        void Pop(unsigned howMany);
        void PopAll();
    protected:
        void CreateStack(unsigned size);
    private:

};

}

#endif // MJMATRIXSTACK_H
