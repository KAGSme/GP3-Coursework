#include "cTransform.h"



glm::mat4 cTransform::updateTransformMatrix()
{
	m_transformMatrix = glm::translate(glm::mat4(1.f), m_pos);
	glm::mat4 currentRotate = glm::mat4_cast(m_rotation);
	m_transformMatrix = m_transformMatrix * currentRotate;
	m_transformMatrix = glm::scale(m_transformMatrix, m_scale);

	m_forward = glm::vec3(0, 0, 1) * glm::mat3(currentRotate);
	m_up = glm::vec3(0, 1, 0) * glm::mat3(currentRotate);
	m_right = glm::vec3(1, 0, 0) * glm::mat3(currentRotate);

	m_isDirty = false;
	return m_transformMatrix;
}

cTransform::cTransform()
{
}


cTransform::~cTransform()
{
}

glm::vec3 cTransform::getRotationEuler()
{
	return glm::degrees(glm::eulerAngles(m_rotation));
}

void cTransform::setRotationEuler(glm::vec3 newRotation)
{
	glm::quat qPitch = glm::angleAxis(glm::radians(newRotation.x), glm::vec3(1, 0, 0));
	glm::quat qYaw = glm::angleAxis(glm::radians(newRotation.y), glm::vec3(0, 1, 0));
	glm::quat qRoll = glm::angleAxis(glm::radians(newRotation.z), glm::vec3(0, 0, 1));
	m_rotation = qPitch * qYaw * qRoll;
	m_rotation = glm::normalize(m_rotation);

	m_isDirty = true;
}

void cTransform::addRotationEuler(glm::vec3 deltaRotation)
{
	glm::quat delta = glm::quat(glm::radians(deltaRotation));
	m_rotation = delta * m_rotation;
	m_rotation = glm::normalize(m_rotation);

	m_isDirty = true;
}

void cTransform::addRotation(glm::quat deltaRotation)
{
	m_rotation = deltaRotation * m_rotation;

	m_isDirty = true;
}

