#ifndef _CLASER_H
#define _CLASER_H

#include "GameConstants.h"
#include "cActor.h"

class cLaser : public cActor
{
public:
	cLaser();

	virtual void update(float elapsedTime);

	~cLaser();

};
#endif