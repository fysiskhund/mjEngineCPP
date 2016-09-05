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
mjMatrixStack::~mjMatrixStack()
{
    for (unsigned i = 0; i < maxSize; i++)
    {
        delete[] mStack[i];
    }
    delete[]  mStack;
}

void mjMatrixStack::CreateStack(unsigned size)
{
    mStack = new float * [size];
    LOGI("%s %d: new %s", __FILE__, __LINE__, "float * (createstack)");
    for(unsigned i = 0; i < size; i++)
    {
        mStack[i] = new float[16];
        LOGI("%s %d: new %s", __FILE__, __LINE__, "float 16 (createStack)");
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
void mjMatrixStack::Pop(unsigned howMany)
{
    for(unsigned i = 0; i < howMany; i++)
	{
		Pop();
	}
}
void mjMatrixStack::PopAll()
{
	currentIndex = 0;
	current = mStack[currentIndex];
}

}
