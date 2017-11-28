#include "cSceneMgr.h"

cSceneMgr::cSceneMgr()
{
}


cSceneMgr::~cSceneMgr()
{
}

cSceneMgr* cSceneMgr::getInstance()
{
	if (m_instance == nullptr)
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
		iter->render();
	}
}
