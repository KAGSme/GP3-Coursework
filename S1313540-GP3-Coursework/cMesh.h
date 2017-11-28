#ifndef _CMESH_H
#define _CMESH_H

#include "GameConstants.h"
#include "windowOGL.h"
#include "glm\glm.hpp"
#include "glx\glext.h"
#include "wglext.h"
#include "cShader.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

class cMesh
{
public:
	//mesh data
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<cTexture*> m_textures;
	cMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<cTexture*> textures);
	~cMesh();
	void renderMesh(cShader shader);
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

#endif
