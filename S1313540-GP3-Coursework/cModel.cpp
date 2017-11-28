#include "cModel.h"

void cModel::RenderModel(cShader shader)
{
	for (auto iter = m_meshes.begin(); iter != m_meshes.end(); iter++) 
	{
		iter->renderMesh(shader);
	}
}

void cModel::loadModel(std::string path)
{
	Assimp::Importer imp;
	const aiScene *scene = imp.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << imp.GetErrorString() << std::endl;
		return;
	}
	m_directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void cModel::processNode(aiNode * node, const aiScene * scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
	}
	//then do the same for each of its chilren
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

cMesh cModel::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<cTexture*> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) 
	{
		Vertex vertex;

		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vector2d;
			vector2d.x = mesh->mTextureCoords[0][i].x;
			vector2d.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vector2d;
		}
		else vertex.texCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<cTexture*> dMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
		textures.insert(textures.end(), dMaps.begin(), dMaps.end());
		std::vector<cTexture*> nMaps = loadMaterialTextures(material, aiTextureType_NORMALS, TextureType::NORMAL);
		textures.insert(textures.end(), nMaps.begin(), nMaps.end());
		std::vector<cTexture*> sMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::SPECULAR);
		textures.insert(textures.end(), sMaps.begin(), sMaps.end());
	}

	return cMesh(vertices, indices, textures);
}

std::vector<cTexture*> cModel::loadMaterialTextures(aiMaterial * mat, aiTextureType type, TextureType cTtype)
{
	std::vector<cTexture*> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{

		aiString str;
		mat->GetTexture(type, i, &str);
		std::string filename = m_directory + '/' + str.C_Str();
		bool skip = false;
		for (unsigned int j = 0; j < m_loadedTextures.size(); j++)
		{
			if (std::strcmp(m_loadedTextures[j]->getPath().c_str(), filename.c_str()) == 0)
			{
				textures.push_back(m_loadedTextures[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			cTexture* texture = new cTexture();
			texture->createTexture(filename.c_str());
			texture->setType(cTtype);
			textures.push_back(texture);
			m_loadedTextures.push_back(texture);
		}
	}
	return textures;
}
