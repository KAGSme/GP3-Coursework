#ifndef _CTRANSFORM_H
#define _CTRANSFORM_H

#include "GameConstants.h"

class cTransform
{
public:
	cTransform();
	~cTransform();

	glm::vec3 getPosition() { return m_pos; }
	glm::vec3 getForward() { return m_forward; }
	glm::vec3 getRight() { return m_right; }
	glm::vec3 getUp() { return m_up; }
	glm::quat getRotation() { return m_rotation; }
	glm::vec3 getRotationEuler();
	glm::vec3 getScale() { return m_scale; }
	glm::mat4 getTransformationMatrix() { if (m_isDirty)return updateTransformMatrix(); else return m_transformMatrix; }

	void setPosition(glm::vec3 newPos) { m_isDirty = true; m_pos = newPos; }
	void addPosition(glm::vec3 deltaPos) { m_isDirty = true; m_pos += deltaPos; }
	void setRotation(glm::quat newRotation) { m_isDirty = true; m_rotation = newRotation; }
	void setRotationEuler(glm::vec3 newRotation);
	void addRotationEuler(glm::vec3 deltaRotation);
	void addRotation(glm::quat deltaRotation);
	void setScale(glm::vec3 newScale) { m_isDirty = true; m_scale = newScale; }
	void addScale(glm::vec3 deltaScale) { m_isDirty = true; m_scale += deltaScale; }

private:
	glm::vec3 m_pos, m_scale, m_forward, m_right, m_up;
	glm::quat m_rotation;
	glm::mat4 m_transformMatrix;

	bool m_isDirty = false;
	glm::mat4 updateTransformMatrix();
};

#endif
