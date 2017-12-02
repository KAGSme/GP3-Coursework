#ifndef _WINDOWOGL_H
#define _WINDOWOGL_H

#include <windows.h>
#include "GL/glew.h"
#include "GL/glut.h"

class windowOGL 
{
public:
    windowOGL();

	bool initOGL(int width, int height);
	//bool initOpenGL();
	void renderOGL(float rotAngle);
    void shutdown();

    void onResize(int width, int height);
	void setOrtho2D(int width, int height);
	void setProjection3D(int width, int height);

private:
	//HGLRC	 m_hrc;	//openGL rendering context
};

#endif
