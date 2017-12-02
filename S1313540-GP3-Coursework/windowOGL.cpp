#include "windowOGL.h"

windowOGL::windowOGL()
{

}

bool windowOGL::initOGL(int width, int height)
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glClearStencil(0);                          // clear stencil buffer
	glClearDepth(1.0f);                         // 0 is near, 1 is far
	glDepthFunc(GL_LEQUAL);
	onResize(width, height);

    //Return success
    return true;
}

/*bool windowOGL::initOpenGL()
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(cWNDManager::getInstance()->getWNDDC(), &pfd);

	if (nPixelFormat == 0) return false;

	BOOL bResult = SetPixelFormat(cWNDManager::getInstance()->getWNDDC(), nPixelFormat, &pfd);

	if (!bResult) return false;

	HGLRC tempContext = wglCreateContext(cWNDManager::getInstance()->getWNDDC());
	wglMakeCurrent(cWNDManager::getInstance()->getWNDDC(), tempContext);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		OutputDebugString("GLEW is not initialized!");
	}

	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 1,
		WGL_CONTEXT_FLAGS_ARB, 0,
		0
	};

	if (wglewIsSupported("WGL_ARB_create_context") == 1)
	{
		m_hrc = wglCreateContextAttribsARB(cWNDManager::getInstance()->getWNDDC(), 0, attribs);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempContext);
		wglMakeCurrent(cWNDManager::getInstance()->getWNDDC(), m_hrc);
	}
	else
	{	//It's not possible to make a GL 3.x context. Use the old style context (GL 2.1 and before)
		m_hrc = tempContext;
	}

	//Checking GL version
	const GLubyte *GLVersionString = glGetString(GL_VERSION);

	//Or better yet, use the GL3 way to get the version number
	int OpenGLVersion[2];
	glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);

	if (!m_hrc) return false;

	return true;
}*/

void windowOGL::renderOGL(float rotAngle)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void windowOGL::shutdown()
{

}

void windowOGL::onResize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void windowOGL::setOrtho2D(int width, int height)
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, 0.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void windowOGL::setProjection3D(int width, int height)
{
	onResize(width, height);
}