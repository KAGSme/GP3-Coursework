#include "cMesh.h"

cMesh::~cMesh()
{
}

cMesh::cMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<cTexture*> textures)
{
	m_vertices = vertices;
	m_indices = indices;
	m_textures = textures;

	setupMesh();
}

void cMesh::renderMesh(cShader shader)
{
	unsigned int diffuseNr = 1;
	unsigned int normalNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < m_textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE + i);

		std::string number;
		std::string name;
		TextureType t = m_textures[i]->getType();

		switch (t)
		{
		case TextureType::DIFFUSE:
			number = std::to_string(diffuseNr++);
			name = "texture_diffuse";
			break;
		case TextureType::NORMAL:
			number = std::to_string(normalNr++);
			name = "texture_specular";
			break;
		case TextureType::SPECULAR:
			number = std::to_string(specularNr++);
			name = "texture_specular";
			break;
		}

		shader.setFloat(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, m_textures[i]->getTexture());

	}
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void cMesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int),&m_indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);
}