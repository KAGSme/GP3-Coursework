#pragma once
#include "cActor.h"
#include "cCamera.h"
class cFreeCam :
	public cActor
{
private:
	cInputMgr* m_InputMgr;
	cCamera* m_camera;
	float m_sensitivity = 0.5;
public:
	cFreeCam();

	void attachInputMgr(cInputMgr* inputMgr);
	void attachCamera(cCamera* camera);
	virtual void update(float elapsedTime);
	virtual void render();

	void moveVertical(float state);
	void rotHorizontal(float state);

	~cFreeCam();
};

