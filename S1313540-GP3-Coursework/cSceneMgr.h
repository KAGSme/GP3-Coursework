#ifndef _CSCENEMGR_H
#define _CSCENEMGR_H

#include "cModel.h"
#include "cTexture.h"
#include "cShader.h"
#include "cActor.h"
#include "cCamera.h"
#include "GameConstants.h"

class cSceneMgr
{
public:
	cSceneMgr();
	~cSceneMgr();
	static cSceneMgr* getInstance();
	void begin();
	void update(float elapsedTime);
	void render();
	void setMainCamera(cCamera* camera) { m_mainCamera = camera; };
	void addTexture(const std::string & filename);
	void addModel(const std::string & filename);
	void addShader(cShader * shader, std::string name);

	void releaseResources();

private:
	static cSceneMgr* m_instance;

	cCamera* m_mainCamera;

	std::map<std::string,cTexture*> m_textures;
	std::map<std::string, cShader*> m_shaders;
	std::map<std::string, cModel*> m_models;
	std::vector<cActor> m_actors;
};

#endif
