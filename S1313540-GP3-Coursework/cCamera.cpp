/*
==========================================================================
ccCamera.h
==========================================================================
*/

#include "cCamera.h"

cCamera::cCamera()
{
	m_viewPort = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ProjectionMatrix = glm::mat4(1.0);
	m_camViewMatrix = glm::mat4(1.0);
}


cCamera::cCamera(int screenWidth, int screenHeight)
{
	m_viewPort = glm::vec4(0, 0, screenWidth, screenHeight);
	m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ProjectionMatrix = glm::mat4(1.0);
	m_camViewMatrix = glm::mat4(1.0);
}

cCamera::~cCamera()
{
	
}

void cCamera::setTheViewPort(int x, int y, int width, int height)
{
	m_viewPort = glm::vec4(x, y, width, height);
	glViewport(x, y, width, height);
}

const glm::vec4 cCamera::getTheViewPort()
{
	return m_viewPort;
}

void cCamera::setTheProjectionMatrix(float fov, float aspectRatio, float nearCP, float farCP)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearCP, farCP);
}

void cCamera::setTheCameraPos(glm::vec3 pos)
{
	m_cameraPos = pos;
}

glm::vec3 cCamera::getTheCameraPos()
{
	return m_cameraPos;
}

void cCamera::setTheCameraUpVector(glm::vec3 camPosUpVec)
{
	m_cameraUpVector = camPosUpVec;
}

glm::vec3 cCamera::getTheCameraUpVector()
{
	return m_cameraUpVector;
}

void cCamera::setTheCameraLookAt(glm::vec3 camLookAt)
{
	m_cameraLookAt = camLookAt;
}

glm::vec3 cCamera::getTheCameraLookAt()
{
	return m_cameraLookAt;
}

void cCamera::setTheCameraDirection()
{
	m_cameraDirection = glm::normalize(m_cameraPos - m_cameraLookAt);
}

glm::vec3 cCamera::getTheCameraDirection()
{
	return m_cameraDirection;
}

void cCamera::setTheCameraStrafe()
{
	m_cameraStrafe = glm::normalize(glm::cross(m_cameraUpVector, m_cameraDirection));
}

glm::vec3 cCamera::getTheCameraStrafe()
{
	return m_cameraStrafe;
}

void cCamera::setTheCameraAspectRatio(GLfloat width, GLfloat height)
{
	m_AspectRatio = width/height;
}

GLfloat cCamera::getTheCameraAspectRatio()
{
	return m_AspectRatio;
}

glm::mat4 cCamera::getTheProjectionMatrix()
{
	return m_ProjectionMatrix;
}

glm::mat4 cCamera::getTheViewMatrix()
{
	return m_camViewMatrix;
}

void cCamera::setCamViewMatrix()
{
	m_camViewMatrix = glm::lookAt(m_cameraPos, m_cameraLookAt, m_cameraUpVector);
}

void cCamera::setCamViewMatrix(glm::mat4 newMatrix)
{
	m_camViewMatrix = newMatrix;
}

glm::mat4 cCamera::getCamViewMatrix()
{
	return m_camViewMatrix;
}

void cCamera::update()
{
	if (m_parentTransform != nullptr)
	{
		m_parentTransform->getTransformationMatrix();

		m_cameraDirection = -1.f * m_parentTransform->getForward();
		setTheCameraUpVector(m_parentTransform->getUp());

		m_cameraPos = m_parentTransform->GetPosition();
		setTheCameraLookAt(m_cameraPos - m_cameraDirection;

		setCamViewMatrix();
	}
	else
	{
		glm::quat qPitch = angleAxis(radians(pitch), vec3(1, 0, 0));
		glm::quat qYaw = angleAxis(radians(yaw), vec3(0, 1, 0));
		glm::quat qRoll = angleAxis(radians(roll), vec3(0, 0, 1));

		glm::quat orientation = qPitch * qYaw;
		orientation = glm::normalize(orientation);
		glm::mat4 currentRotate = glm::mat4_cast(orientation);

		glm::mat4 currentTranslate = glm::mat4(1.0f);
		currentTranslate = glm::translate(currentTranslate, -m_cameraPos);

		glm::mat4 viewMatrix = currentRotate * currentTranslate;

		m_cameraDirection = -1.f * vec3(0, 0, 1) * mat3(currentRotate);
		setTheCameraUpVector(vec3(0, 1, 0) * mat3(currentRotate));
		m_cameraStrafe = vec3(1, 0, 0) * mat3(currentRotate);

		setCamViewMatrix(viewMatrix);
	}

	setTheProjectionMatrix(45.0f, getTheCameraAspectRatio(), 0.1f, 300.0f);
}

