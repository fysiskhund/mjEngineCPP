#ifndef MJRENDERERDATAGL_H
#define MJRENDERERDATAGL_H

#include <extLibs/util/mjMultiPlatform.h>
#include <graphics/renderer/mjRendererData.h>

namespace mjEngine{


class mjRendererDataGL: public mjRendererData
{
public:
    GLuint vertexArrayID;

    GLuint vertexCoordinatesBufferID;
    GLuint uvComponentsBufferID;
    GLuint normalCoordinatesID;

    GLuint* elementBuffersIDs;
};

}
#endif // MJRENDERERDATAGL_H
