#ifndef _CSHADER_H
#define _CSHADER_H

#include "GL/glew.h"
#include "GL/gl.h"
#include <fstream>
#include <sstream>
#include <iostream>

class cShader
{
public:
	cShader();
	~cShader();

	cShader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void use();

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

private:
	unsigned int ID;
};
#endif // !_CSHADER_H;


