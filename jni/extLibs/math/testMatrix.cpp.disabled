#include <stdio.h>
#include "Matrix.h"

using namespace mjEngine;

int main()
{
	float a[16] = {0,  1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15};
	float b[16] = {16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
	float c[16];
	Matrix4::MultiplyMM(c,0,a,0,b,0);
	
	int k = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%3.3f\t", c[k]);
			k++;
		}
		printf("\n");
	}

return 0;
}