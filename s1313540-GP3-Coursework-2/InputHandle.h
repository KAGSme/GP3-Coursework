#ifndef _INPUT_ACTIONS_H
#define _INPUT_ACTIONS_H

#include "GameConstants.h"

struct InputAction
{
	std::string name = "";
	char state = false;
	char stateOld = true;
	std::vector<char> keys;

public:
	__event void InputActionChange(bool state);
};

struct InputAxis
{
	std::string name = "";
	float state = 0.0f;
	float stateOld;
	std::vector<char> keysPos;
	std::vector<char> keysNeg;

public:
	__event void InputAxisChange(float axis);
};

#endif