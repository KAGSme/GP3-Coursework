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
	float yaw, pitch, roll;
	float test = m_rotation.x * m_rotation.y + m_rotation.z *m_rotation.w;
	if (test > 0.499)
	{
		yaw = 2 * atan2(m_rotation.x, m_rotation.w);
		roll = M_PI / 2;
		pitch = 0;
		return glm::degrees(glm::vec3(pitch, yaw, roll));
	}
	if (test < -0.499)
	{
		yaw = -2 * atan2(m_rotation.x, m_rotation.w);
		roll = -M_PI / 2;
		pitch = 0;
		return glm::degrees(glm::vec3(pitch, yaw, roll));
	}
	float sqx = m_rotation.x * m_rotation.x;
	float sqy = m_rotation.y * m_rotation.y;
	float sqz = m_rotation.z * m_rotation.z;

	yaw = atan2(2 * m_rotation.y* m_rotation.w - 2 * m_rotation.x * m_rotation.z, 1 - 2 * sqy - 2 * sqz);
	roll = asin(2 * test);
	pitch = atan2(2 * m_rotation.x*m_rotation.w - 2 * m_rotation.y*m_rotation.z, 1 - 2 * sqx - 2 * sqz);

	return glm::degrees(glm::vec3(pitch, yaw, roll));
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

