#ifndef _CSHADER_H
#define _CSHADER_H

#include "GameConstants.h"
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
	void setMat4(const std::string &name, glm::mat4* value) const;
	void setVec3(const std::string &name, glm::vec3 value) const;
	void setVec4(const std::string &name, glm::vec4 value) const;


private:
	unsigned int ID;
};
#endif // !_CSHADER_H;


