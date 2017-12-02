#include "cShader.h"



cShader::cShader()
{
}


cShader::~cShader()
{
}

cShader::cShader(const GLchar * vertexPath, const GLchar * fragmentPath)
{

	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		OutputDebugString("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n");
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		OutputDebugString("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
		OutputDebugString(infoLog);
	};

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		OutputDebugString("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
		OutputDebugString(infoLog);
	};

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		OutputDebugString("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
		OutputDebugString(infoLog);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void cShader::use()
{
	glUseProgram(ID);
}

void cShader::setBool(const std::string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void cShader::setInt(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void cShader::setFloat(const std::string & name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void cShader::setMat4(const std::string & name, glm::mat4* value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, false, (const GLfloat*)value);
}

void cShader::setVec3(const std::string & name, glm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void cShader::setVec4(const std::string & name, glm::vec4 value) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value.r, value.g, value.b, value.a);
}



