#ifndef _CMODEL_H
#define _CMODEL_H

#include "GameConstants.h"
#include "cMesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class cModel
{
public:
	//model data
	cModel(char *path)
	{
		loadModel(path);
	}
	void RenderModel(cShader shader);
private:
	std::vector<cTexture*> m_loadedTextures;
	std::vector<cMesh> m_meshes;
	std::string m_directory;

	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	cMesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<cTexture*> loadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureType cTtype);
};
	
#endif
