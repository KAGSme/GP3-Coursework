#pragma once
#include "cModel.h"
#include "cTexture.h"
#include "cShader.h"
#include "cActor.h"
#include "GameConstants.h"
#include <map>

class cSceneMgr
{
public:
	cSceneMgr();
	~cSceneMgr();

	static cSceneMgr* getInstance();
	void begin();
	void update(float elapsedTime);
	void render();

private:
	static cSceneMgr* m_instance;

	std::map<std::string,cTexture*> m_textures;
	std::map<std::string, cShader*> m_shaders;
	std::map<std::string, cModel*> m_models;
	std::vector<cActor> m_actors;
};

