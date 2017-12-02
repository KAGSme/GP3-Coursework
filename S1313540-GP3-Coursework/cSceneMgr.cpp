#include "cSceneMgr.h"

cSceneMgr* cSceneMgr::m_instance = NULL;

cSceneMgr::cSceneMgr()
{
}


cSceneMgr::~cSceneMgr()
{
}

cSceneMgr * cSceneMgr::getInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new cSceneMgr();
	}
	return cSceneMgr::m_instance;
}

void cSceneMgr::begin()
{
	//set up scene here
	//addModel("7h15t5bvooe8-Aventador/Avent.obj");
	addModel("Nanosuit2/nanosuit2.obj");

	addActor(new cFreeCameraActor(), "freeCamera");
	addActor(new cPlayerCarActor(), "playerCar");
	std::string vs = SHADERPATH + "carVS.glsl";
	std::string fs = SHADERPATH + "carFS.glsl";
	addShader(new cShader(vs.c_str(),fs.c_str()), "car");

	for (auto iter : m_actors)
	{
		iter.second->begin();
	}
}

void cSceneMgr::update(float elapsedTime)
{
	for (auto iter : m_actors)
	{
		iter.second->update(elapsedTime);
	}
}

void cSceneMgr::render()
{
	for (auto iter : m_actors)
	{
		iter.second->render(m_mainCamera);
	}
}

void cSceneMgr::addTexture(const std::string & filename)
{
	std:string t = TEXTUREPATH + filename;
	m_textures[filename] = new cTexture(t.c_str());
}

void cSceneMgr::addTexture(cTexture* texture, const std::string & filename)
{
	m_textures[filename] = texture;
}

void cSceneMgr::addModelTexture(const std::string & path)
{
	m_textures[path] = new cTexture(path.c_str());
}


void cSceneMgr::addModel(const std::string & filename)
{
	std:string t = MODELPATH + filename;
	const char* path = t.c_str();
	m_models[filename] = new cModel(path);
}

void cSceneMgr::addShader(cShader * shader, const std::string & name)
{
	m_shaders[name] = shader;
}

void cSceneMgr::addActor(cActor * actor, const std::string & name)
{
	if (m_actors.count(name) == 0)
		m_actors[name] = actor;
}

void cSceneMgr::releaseResources()
{
	for (auto iter = m_textures.begin(); iter != m_textures.end(); iter++)
		delete iter->second;

	for (auto iter = m_models.begin(); iter != m_models.end(); iter++)
		delete iter->second;
}
