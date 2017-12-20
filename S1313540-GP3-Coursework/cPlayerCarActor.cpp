#include "cPlayerCarActor.h"
#include "cSceneMgr.h"



cPlayerCarActor::cPlayerCarActor()
{
}


cPlayerCarActor::~cPlayerCarActor()
{
}

void cPlayerCarActor::begin()
{
	m_model = cSceneMgr::getInstance()->getModel("7h15t5bvooe8-Aventador/Avent.obj");
	m_shader = cSceneMgr::getInstance()->getShader("car");
	m_transform->setPosition(glm::vec3(0, 0, 50));
}

void cPlayerCarActor::update(float elapsedTime)
{
}

void cPlayerCarActor::render(cCamera * camera)
{
	if (!m_shader)
		return;
	if (!camera)
		return;

	m_shader->use();

	glm::mat4 model = m_transform->getTransformationMatrix();
	m_shader->setMat4("Model", &model);
	glm::mat4 VP = camera->getCamViewMatrix() * camera->getTheProjectionMatrix();
	m_shader->setMat4("VP", &VP);

	glm::vec3 camPos = camera->getTheCameraPos();
	m_shader->setVec3("cameraPosition", camPos);

	glm::vec3 mainLightDir(0.5, -0.5, 0);
	m_shader->setVec3("lightDirection", mainLightDir);

	float power = 25;
	m_shader->setFloat("specularPower", power);

	glm::vec4 ambLightColor(0.5, 0.2, 0.2, 0.2);
	m_shader->setVec4("ambientLightColor", ambLightColor);

	glm::vec4 specLightColor(1, 1, 1, 1);
	m_shader->setVec4("specularLightColor", specLightColor);

	glm::vec4 ambMatColor(0.2, 0.2, 0.2, 1);
	m_shader->setVec4("ambientMaterialColor", ambMatColor);

	glm::vec4 difMatColor(0.2, 0.2, 0.2, 1);
	m_shader->setVec4("diffuseMaterialColour", difMatColor);

	m_model->RenderModel(*m_shader);
}
