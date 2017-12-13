/*
=================
cTexture.cpp
- CPP file for class definition - IMPLEMENTATION
- CPP file for the cTexture class
=================
*/
#include "cTexture.h"

/*
=================
- Data constructor initializes the OpenGL Texture ID object
- Is always called, thus ensures all OpenGL Texture ID objects are in a consistent state.
=================
*/
cTexture::cTexture()
{
	cTexture::GLTextureID = NULL;
}

cTexture::cTexture(LPCSTR theFilename)
{
	cTexture::createTexture(theFilename);
}

/*
=================
- Destructor.
=================
*/
cTexture::~cTexture()
{
}

/*
=================
- create the texture for use.
=================
*/
bool cTexture::createTexture(LPCSTR theFilename) 	// create the texture for use.
{
	m_path = theFilename;

	GLTextureID = SOIL_load_OGL_texture(m_path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (0 == GLTextureID) return false;

	return true;
}
/*
=================
- return the texture.
=================
*/
GLuint cTexture::getTexture()        // return the texture.
{
	return cTexture::GLTextureID;
}

/*
=================
- Return width of texture.
=================
*/
GLsizei cTexture::getTWidth() 						// Return width of texture;
{
	return textureWidth;
}
/*
=================
- Return height of texture.
=================
*/
GLsizei cTexture::getTHeight() 						// Return height of texture;
{
	return textureHeight;
}