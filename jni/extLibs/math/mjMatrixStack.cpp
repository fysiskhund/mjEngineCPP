#include "mjMatrixStack.h"

namespace mjEngine{

mjMatrixStack::mjMatrixStack()
{
    CreateStack(maxSize);
}

mjMatrixStack::mjMatrixStack(unsigned size)
{
    maxSize = size;
    CreateStack(maxSize);
}

void mjMatrixStack::CreateStack(unsigned size)
{
    mStack = new float * [size];
    for(unsigned i = 0; i < size; i++)
    {
        mStack[size] = new float[16];
    }
    current = mStack[0];
    Matrix4::SetIdentityM(mStack[0], 0);
}

void mjMatrixStack::Push(float* m)
{
    if (currentIndex < maxSize-1)
    {
        Matrix4::MultiplyMM(mStack[currentIndex+1], 0, mStack[currentIndex], 0, m, 0);
        currentIndex++;
        current = mStack[currentIndex];
    }
}

void mjMatrixStack::Pop()
{
    if (currentIndex > 0)
    {
        currentIndex--;
        current = mStack[currentIndex];
    }
}

}
