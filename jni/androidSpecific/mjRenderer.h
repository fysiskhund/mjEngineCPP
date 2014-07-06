#ifndef MJRENDERER_H
#define MJRENDERER_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

namespace mjEngine{

class mjRenderer{
public:
	mjRenderer();
	void DrawModel(mjModel* model);
private:
};
} // namespace mj

#endif
