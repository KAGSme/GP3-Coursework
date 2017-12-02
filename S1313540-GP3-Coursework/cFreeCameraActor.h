#pragma once
#include "cActor.h"
#include "cCamera.h"
#include "cSceneMgr.h"

class cFreeCameraActor :
	public cActor
{
public:
	cFreeCameraActor();
	~cFreeCameraActor();

	void begin() override;
	void update(float elapsedTime) override;

	void moveVertical(float state);
	void moveHorizontal(float state);
	void InputSpeedBoostHold(bool state);

private:
	cCamera* m_camera;
	float speed = 20;
	float standardSpeed = 20;
	float boostSpeed = 50;
	float currentElapsedTime;
};

