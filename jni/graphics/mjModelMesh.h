#ifndef MJMODELMESH_H
#define MJMODELMESH_H

class mjModelMesh
{
public:
	char* name;
	char* material;
	int* drawOrder;

	mjModelMesh();
};

#endif
