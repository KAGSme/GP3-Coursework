#include "cFreeCam.h"



cFreeCam::cFreeCam()
{
}

void cFreeCam::attachInputMgr(cInputMgr * inputMgr)
{
	m_InputMgr = inputMgr;

	InputAxis* iaV = m_InputMgr->getInputAxisState("camVertical");
	if (iaV)
		__hook(&InputAxis::InputAxisChange, iaV, &cFreeCam::moveVertical);

	InputAxis* iaH = m_InputMgr->getInputAxisState("camHorizontal");
	if (iaH)
		__hook(&InputAxis::InputAxisChange, iaH, &cFreeCam::rotHorizontal);
}

void cFreeCam::attachCamera(cCamera * camera)
{
	m_camera = camera;
}

float worldElapsedTime = 0;
void cFreeCam::update(float elapsedTime)
{
	worldElapsedTime = elapsedTime;
	m_camera->update();
}

void cFreeCam::render()
{
}


void cFreeCam::moveVertical(float state)
{
	m_transform.addPosition(state * 50.0f * getTransform().getForward() * worldElapsedTime);
}

void cFreeCam::rotHorizontal(float state)
{
	m_transform.addRotationEuler(glm::vec3(0, state *25.0f * worldElapsedTime, 0));
}

cFreeCam::~cFreeCam()
{
	InputAxis* iaV = m_InputMgr->getInputAxisState("camVertical");
	if (iaV)
		__unhook(&InputAxis::InputAxisChange, iaV, &cFreeCam::moveVertical);

	InputAxis* iaH = m_InputMgr->getInputAxisState("camHorizontal");
	if (iaH)
		__unhook(&InputAxis::InputAxisChange, iaH, &cFreeCam::rotHorizontal);
}
