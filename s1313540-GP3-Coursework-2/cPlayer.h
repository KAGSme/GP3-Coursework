#ifndef _CPLAYER_H
#define _CPLAYER_H

#include "GameConstants.h"
#include "tardisWarsGame.h"
#include "cActor.h"
#include "cInputMgr.h"

class cPlayer : public cActor
{
private:
	cInputMgr* m_InputMgr;
public:
	cPlayer();
	void attachInputMgr(cInputMgr* inputMgr);
	virtual void update(float elapsedTime);
	virtual void render();

	void moveVertical(float state);
	void moveHorizontal(float state);
	void Jump(bool state);

	~cPlayer();
};
#endif