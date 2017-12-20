#pragma once
#include "cModel.h"
#include "cCamera.h"
class cFreeCam :
	public cModel
{
private:
	cInputMgr* m_InputMgr;
	cCamera* m_camera;
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

