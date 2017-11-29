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
	for (auto iter = m_actors.begin(); iter != m_actors.end(); iter++)
	{
		iter->begin();
	}
}

void cSceneMgr::update(float elapsedTime)
{
	for (auto iter = m_actors.begin(); iter != m_actors.end(); iter++)
	{
		iter->update(elapsedTime);
	}
}

void cSceneMgr::render()
{
	for (auto iter = m_actors.begin(); iter != m_actors.end(); iter++)
	{
		iter->render(m_mainCamera);
	}
}

void cSceneMgr::addTexture(const std::string & filename)
{
}

void cSceneMgr::addModel(const std::string & filename)
{
}

void cSceneMgr::addShader(cShader * shader, std::string name)
{
}

void cSceneMgr::releaseResources()
{
}
