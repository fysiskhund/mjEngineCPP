#ifndef MJSHADERRESOURCE_H
#define MJSHADERRESOURCE_H

#include <extLibs/util/mjMultiPlatform.h>
#include <util/mjResource.h>
#include <graphics/mjShader.h>


namespace mjEngine {

class mjShaderResource: public mjResource
{
public:
    mjShaderResource();
    GLuint glProgramID = 0;
    int shaderListIndex;
    mjShader* shader;

};

}

#endif // MJSHADERRESOURCE_H
