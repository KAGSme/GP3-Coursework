#include "cEnemy.h"

cEnemy::cEnemy() : cActor()
{
	
}

void cEnemy::randomise()
{
	if (rand() % 2 == 0)
	{
		cActor::m_mdlPosition.x = -PLAYFIELDX;
	}
	else
	{
		cActor::m_mdlPosition.x = PLAYFIELDX;
	}
	cActor::m_mdlPosition.y = 0.0f;
	cActor::m_mdlPosition.z = (rand() / (float)RAND_MAX) * 300.0f;   // random number as a float between 0 & 1
	cActor::m_mdlRotation = (rand() / (float)RAND_MAX) * 2 * 3.14f;
	cActor::m_mdlDirection.x = -(float)glm::sin(cActor::m_mdlRotation);
	cActor::m_mdlDirection.z = (float)glm::cos(cActor::m_mdlRotation);
	cActor::m_mdlSpeed = m_EnemyMinSpeed + rand() / (float)RAND_MAX * m_EnemyMaxSpeed;
	cActor::m_IsActive = true;
}

void cEnemy::update(float elapsedTime)
{
	cActor::m_mdlPosition += cActor::m_mdlDirection * cActor::m_mdlSpeed * elapsedTime;
	if (cActor::m_mdlPosition.x > PLAYFIELDX)
		cActor::m_mdlPosition.x -= 2 * PLAYFIELDX;
	if (cActor::m_mdlPosition.x < -PLAYFIELDX)
		cActor::m_mdlPosition.x += 2 * PLAYFIELDX;
	if (cActor::m_mdlPosition.z > PLAYFIELDZ)
		cActor::m_mdlPosition.z -= 2 * PLAYFIELDZ;
	if (cActor::m_mdlPosition.z < -PLAYFIELDZ)
		cActor::m_mdlPosition.z += 2 * PLAYFIELDZ;
}

cEnemy::~cEnemy()
{

}

