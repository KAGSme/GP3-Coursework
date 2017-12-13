#include "cFreeCameraActor.h"



cFreeCameraActor::cFreeCameraActor()
{
}


cFreeCameraActor::~cFreeCameraActor()
{
	cInputMgr* iM = cInputMgr::getInstance();

	InputAxis* iaV = iM->getInputAxisState("Vertical");
	if (iaV)
		__unhook(&InputAxis::InputAxisChange, iaV, &cFreeCameraActor::moveVertical);

	InputAxis* iaH = iM->getInputAxisState("Horizontal");
	if (iaH)
		__unhook(&InputAxis::InputAxisChange, iaH, &cFreeCameraActor::moveHorizontal);

	InputAction* iaS = iM->getInputActionState("SpeedBoost");
	if (iaS)
		__unhook(&InputAction::InputActionChange, iaS, &cFreeCameraActor::InputSpeedBoostHold);
}

void cFreeCameraActor::begin()
{
	m_camera = new cCamera();
	m_camera->setParentTransform(m_transform);
	cSceneMgr::getInstance()->setMainCamera(m_camera);

	cInputMgr* iM = cInputMgr::getInstance();

	InputAxis* iaV = iM->getInputAxisState("Vertical");
	if (iaV)
		__hook(&InputAxis::InputAxisChange, iaV, &cFreeCameraActor::moveVertical);

	InputAxis* iaH = iM->getInputAxisState("Horizontal");
	if (iaH)
		__hook(&InputAxis::InputAxisChange, iaH, &cFreeCameraActor::moveHorizontal);

	InputAction* iaS = iM->getInputActionState("SpeedBoost");
	if (iaS)
		__hook(&InputAction::InputActionChange, iaS, &cFreeCameraActor::InputSpeedBoostHold);
}

void cFreeCameraActor::update(float elapsedTime)
{
	currentElapsedTime = elapsedTime;

	//get mouse movement
	glm::ivec2 deltaPos = cInputMgr::getInstance()->mouseXYDelta();
	std::string sDeltaPos = "x: " + to_string(deltaPos.x) + ", y: " + to_string(deltaPos.y) + "\n";
	float deltaPitch = (float)deltaPos.y;
	float deltaYaw = (float)deltaPos.x;

	glm::quat qPitch = glm::quat(glm::vec3(glm::radians(deltaPitch), 0, 0));
	glm::quat qYaw = glm::quat(glm::vec3(0, glm::radians(deltaYaw), 0));

	m_transform->getTransformationMatrix();

	//combine rotations this way to eliminate unwanted roll
	glm::quat total = qPitch * m_transform->getRotation() * qYaw;
	m_transform->setRotation(total);
}

void cFreeCameraActor::moveVertical(float state)
{
	if (state >0)OutputDebugString("moveVertical pos\n");
	else OutputDebugString("moveVertical neg\n");
	m_transform->addPosition(m_camera->getTheCameraDirection() * currentElapsedTime * speed * state);
}

void cFreeCameraActor::moveHorizontal(float state)
{
	if(state > 0)OutputDebugString("moveHorizontal Pos\n");
	else OutputDebugString("moveHorizontal Neg\n");
	m_transform->addPosition(m_camera->getTheCameraStrafe() * currentElapsedTime * speed * state);
}

void cFreeCameraActor::InputSpeedBoostHold(bool state)
{
	if (state)
	{
		speed = boostSpeed;
		OutputDebugString("speedBoost true\n");
	}
	else
	{
		speed = standardSpeed;
		OutputDebugString("speedBoost false\n");
	}
}
