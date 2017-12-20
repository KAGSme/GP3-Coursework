#include "cPlayer.h"

cPlayer::cPlayer() : cModel()
{

}

void cPlayer::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}

void cPlayer::update(float elapsedTime)
{
	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		m_transform.addRotationEuler(glm::vec3(0, 5.0f * elapsedTime, 0));
		GameOutputDebugString("Current Rotation " + to_string(getTransform().getRotationEuler().x)+ " " + to_string(getTransform().getRotationEuler().y)+ " " + to_string(getTransform().getRotationEuler().z));
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		m_transform.addRotationEuler(glm::vec3(0, -5.0f * elapsedTime, 0));
		GameOutputDebugString("Current Rotation " + to_string(getTransform().getRotationEuler().x) + " " + to_string(getTransform().getRotationEuler().y) + " " + to_string(getTransform().getRotationEuler().z));
	}
	if (m_InputMgr->isKeyDown(VK_UP))
	{
		m_transform.addPosition(50.0f * getTransform().getForward() * elapsedTime);
	}
	if (m_InputMgr->isKeyDown(VK_DOWN))
	{
		m_transform.addPosition(-50.0f * getTransform().getForward() * elapsedTime);
	}

	if (m_InputMgr->isKeyDown(VK_SPACE))
	{
		glm::vec3 mdlLaserDirection;
		mdlLaserDirection = getTransform().getForward();
		GameOutputDebugString("Laser Direction" + to_string(mdlLaserDirection.x) + to_string(mdlLaserDirection.y) + to_string(mdlLaserDirection.z));

		// Add new bullet sprite to the vector array
		theTardisLasers.push_back(new cLaser);
		int numLasers = theTardisLasers.size() - 1;
		theTardisLasers[numLasers]->setDirection(mdlLaserDirection);
		theTardisLasers[numLasers]->setRotation(0.0f);
		theTardisLasers[numLasers]->setScale(glm::vec3(1, 1, 1));
		theTardisLasers[numLasers]->setSpeed(5.0f);
		theTardisLasers[numLasers]->setPosition(this->getPosition() + mdlLaserDirection);
		theTardisLasers[numLasers]->setIsActive(true);
		//theTardisLasers[numLasers]->setMdlDimensions(theLaser.getModelDimensions());
		theTardisLasers[numLasers]->update(elapsedTime);
		// play the firing sound
		m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
	}

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin(); laserIterartor != theTardisLasers.end(); ++laserIterartor)
	{
		(*laserIterartor)->update(elapsedTime);
		for (vector<cEnemy*>::iterator enemyIterator = theEnemy.begin(); enemyIterator != theEnemy.end(); ++enemyIterator)
		{
			if ((*enemyIterator)->SphereSphereCollision((*laserIterartor)->getPosition(), (*laserIterartor)->getMdlRadius()))
			{
				// if a collision set the bullet and spaceship to false
				(*enemyIterator)->setIsActive(false);
				(*laserIterartor)->setIsActive(false);
				// play the explosion sound.
				m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
			}
		}
	}

	vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin();
	while (laserIterartor != theTardisLasers.end())
	{
		if ((*laserIterartor)->isActive() == false)
		{
			laserIterartor = theTardisLasers.erase(laserIterartor);
		}
		else
		{
			++laserIterartor;
		}
	}

	vector<cEnemy*>::iterator enemyIterartor = theEnemy.begin();
	while (enemyIterartor != theEnemy.end())
	{
		if ((*enemyIterartor)->isActive() == false)
		{
			enemyIterartor = theEnemy.erase(enemyIterartor);
		}
		else
		{
			++enemyIterartor;
		}
	}

	// Find out what direction we should be thrusting, using rotation.
	glm::vec3 mdlVelocityAdd;
	mdlVelocityAdd.x = -(float)glm::sin(glm::radians(m_mdlRotation));  // Remember to adjust for radians
	mdlVelocityAdd.y = 0.0f;
	mdlVelocityAdd.z = -(float)glm::cos(glm::radians(m_mdlRotation));

	m_mdlRotation -= rotationAngle;

	mdlVelocityAdd *= translationZ;
	m_mdlDirection += mdlVelocityAdd;

	m_mdlPosition += m_mdlDirection * m_mdlSpeed *elapsedTime;
	m_mdlDirection *= 0.95f;

	rotationAngle = 0;
	translationZ = 0;
}

void cPlayer::render()
{
	m_model->renderMdl(getTransform().getPosition(), getTransform().getRotationEuler().y, getScale());
}

cPlayer::~cPlayer()
{

}