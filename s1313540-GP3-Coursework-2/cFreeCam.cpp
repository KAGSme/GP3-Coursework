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
	m_camera->setParentTransform(&m_transform);
}

float worldElapsedTime0 = 0;
void cFreeCam::update(float elapsedTime)
{
	worldElapsedTime0 = elapsedTime;

	//get mouse movement
	glm::ivec2 deltaPos = cInputMgr::getInstance()->mouseXYDelta();
	std::string sDeltaPos = "x: " + to_string(deltaPos.x) + ", y: " + to_string(deltaPos.y) + "\n";
	GameOutputDebugString(sDeltaPos);
	float deltaPitch = -(float)deltaPos.y;
	float deltaYaw = (float)deltaPos.x;

	glm::quat qPitch = glm::quat(glm::vec3(glm::radians(deltaPitch * m_sensitivity), 0, 0));
	glm::quat qYaw = glm::quat(glm::vec3(0, glm::radians(deltaYaw * m_sensitivity), 0));

	m_transform.getTransformationMatrix();

	//combine rotations this way to eliminate unwanted roll
	glm::quat total = qPitch * m_transform.getRotation() * qYaw;
	m_transform.setRotation(total);
	getTransform();

	m_camera->update();
}

void cFreeCam::render()
{
}


void cFreeCam::moveVertical(float state)
{
	m_transform.addPosition(state * 50.0f * getTransform()->getForward() * worldElapsedTime0);
}

void cFreeCam::rotHorizontal(float state)
{
	m_transform.addPosition(state * 50.0f * -getTransform()->getRight() * worldElapsedTime0);
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
