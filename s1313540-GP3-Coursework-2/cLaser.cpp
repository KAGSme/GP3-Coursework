#include "cLaser.h"

cLaser::cLaser() : cActor()
{

}

void cLaser::update(float elapsedTime)
{
	cActor::m_mdlPosition += cActor::m_mdlDirection * cActor::m_mdlSpeed * elapsedTime;
	if (cActor::m_mdlPosition.x > PLAYFIELDX ||
		cActor::m_mdlPosition.x < -PLAYFIELDX ||
		cActor::m_mdlPosition.z > PLAYFIELDZ ||
		cActor::m_mdlPosition.z < -PLAYFIELDZ)
		cActor::m_IsActive = false;

}

cLaser::~cLaser()
{

}
