/*
=================
cTexture.h
- Header file for class definition - SPECIFICATION
- Header file for the cD3DXTexture class
=================
*/
#ifndef _CTEXTURE_H
#define _CTEXTURE_H
#include "GameConstants.h"

enum TextureType {
	DIFFUSE,
	NORMAL,
	SPECULAR
};

class cTexture
{
private:
	GLuint GLTextureID;
	GLuint aTextureInfo;
	GLsizei textureWidth;
	GLsizei textureHeight;
	ILuint ilTextureID;
	ILubyte *txData;
	TextureType m_type;
	std::string m_path;

public:
	cTexture();
	cTexture(LPCSTR theFilename);
	~cTexture();
	bool createTexture(LPCSTR theFilename);		// create the texture for use.
	GLuint getTexture();						// return the texture.
	GLsizei getTWidth();						// Return width of texture;
	GLsizei getTHeight();						// Return height of texture;
	TextureType getType() { return m_type; };
	void setType(TextureType type) { m_type = type; };
	std::string getPath() { return m_path; };
};
#endif