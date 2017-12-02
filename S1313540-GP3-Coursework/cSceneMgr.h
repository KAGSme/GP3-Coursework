#ifndef _CSCENEMGR_H
#define _CSCENEMGR_H

#include "cModel.h"
#include "cTexture.h"
#include "cShader.h"
#include "cActor.h"
#include "cCamera.h"
#include "GameConstants.h"
#include "cPlayerCarActor.h"
#include "cFreeCameraActor.h"

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
	void addTexture(cTexture* texture, const std::string & filename);
	void addModelTexture(const std::string & path);
	void addModel(const std::string & filename);
	void addShader(cShader * shader, const std::string & name);
	void addActor(cActor * actor, const std::string & name);
	cModel* getModel(std::string name) { return m_models[name]; };
	cActor* getActor(std::string name) { return m_actors[name]; };
	cShader* getShader(std::string name) { return m_shaders[name]; };

	void releaseResources();

private:
	static cSceneMgr* m_instance;

	cCamera* m_mainCamera;

	std::map<std::string,cTexture*> m_textures;
	std::map<std::string, cShader*> m_shaders;
	std::map<std::string, cModel*> m_models;
	std::map<std::string, cActor*> m_actors;
};

#endif
