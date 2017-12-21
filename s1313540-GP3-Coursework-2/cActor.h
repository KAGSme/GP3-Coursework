#ifndef _CACTOR_H
#define _CACTOR_H

#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cModelLoader.h"
#include "GameConstants.h"
//#include "tardisWarsGame.h"

class cActor
{
public:
	cActor();
	void setPosition(glm::vec3 mdlPosition);
	void setRotation(GLfloat mdlRotation);
	void setDirection(glm::vec3 mdlDirection);
	void setSpeed(float mdlSpeed);
	void setIsActive(bool mdlIsActive);
	void setMdlDimensions(mdlDimensions mdlDims);
	void setMdlRadius(float mdlRadius);
	void setScale(glm::vec3 mdlScale);
	void setTextureID(GLuint theTextureID);

	cTransform * getTransform() { m_transform.getTransformationMatrix(); return &m_transform; }

	glm::vec3 getPosition();
	GLfloat getRotation();
	glm::vec3 getDirection();
	float getSpeed();
	bool isActive();
	mdlDimensions getMdlDimensions();
	float getMdlRadius();
	glm::vec3 getScale();

	void initialise(glm::vec3 mdlPosition, GLfloat mdlRotation, glm::vec3 mdlScale, glm::vec3 mdlDirection, float mdlSpeed, bool mdlIsActive);
	virtual void update(float elapsedTime) = 0;     // will be defined by inherting class
	virtual void render() {}; //will be defined by inheriting class
	bool SphereSphereCollision(glm::vec3 mdlPosition, float mdlRadius);

	void attachInputMgr(cInputMgr* inputMgr);  // Attach the Input Manager
	void attachSoundMgr(cSoundMgr* soundMgr);  // Attach the Sound Manager
	void attachModel(cModelLoader* model);

	~cActor();

private:
	float lengthSQRD(glm::vec3 mdlLength);
	GLuint m_TextureID;

protected:
	// Set the position of the model in world space, and set the rotation.
	glm::vec3 m_mdlPosition;
	GLfloat m_mdlRotation;
	glm::vec3 m_mdlScale;
	glm::vec3 m_mdlDirection;
	mdlDimensions m_Dimensions; // (width, height, depth)
	float m_mdlSpeed;
	bool m_IsActive;
	float m_mdlRadius;

	cTransform m_transform;
	cModelLoader * m_model;

	cInputMgr* m_InputMgr;
	cSoundMgr* m_SoundMgr;

};
#endif
