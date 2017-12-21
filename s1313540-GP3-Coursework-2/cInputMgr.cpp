/*
== == == == == == == == =
cInputMgr.h
- Header file for class definition - SPECIFICATION
- Header file for the InputMgr class
== == == == == == == == =
*/

#include "cInputMgr.h"
#include "cWNDManager.h"

cInputMgr* cInputMgr::pInstance = NULL;

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cInputMgr* cInputMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cInputMgr();
	}
	return cInputMgr::pInstance;
}

/*
=================================================================================
Constructor
=================================================================================
*/
cInputMgr::cInputMgr()
{
	for (int key = 0; key < 256; key++)		// clear key down buffer
	{
		keysDownBuffer[key] = false;
	}
	for (int key = 0; key < 256; key++)			// clear key pressed array
	{
		keysPressedBuffer[key] = false;
	}

	mousePos.x = 0;                         // screen X
	mousePos.y = 0;                         // screen Y
	leftMouseBtn = false;               // true if left mouse button is down
	middleMouseBtn = false;               // true if middle mouse button is down
	rightMouseBtn = false;               // true if right mouse button is down

}

/*
=============================================================================
Set true in the keysDown and keysPessed array for this key
=============================================================================
*/
void cInputMgr::keyDown(WPARAM wParam)
{
	if (wParam < 256)
	{
		keysDownBuffer[wParam] = true;    // update keysDown array
		keysPressedBuffer[wParam] = true; // update keysPressed array
	}
}

/*
=============================================================================
Set false in the keysDown array for this key
=============================================================================
*/
void cInputMgr::keyUp(WPARAM wParam)
{
	if (wParam < 256)
	{
		keysDownBuffer[wParam] = false;
	}
}
/*
=============================================================================
Returns true if the specified VIRTUAL KEY is down, otherwise false.
=============================================================================
*/
bool cInputMgr::isKeyDown(int vkey)
{
	if (vkey < 256)
	{
		return keysDownBuffer[vkey];
	}
	else
	{
		return false;
	}
}
/*
=============================================================================
Return true if the specified VIRTUAL KEY has been pressed
=============================================================================
*/
bool cInputMgr::wasKeyPressed(int vkey)
{
	if (vkey < 256)
	{
		return keysPressedBuffer[vkey];
	}
	else
	{
		return false;
	}
}
/*
=============================================================================
Return true if any key was pressed
=============================================================================
*/
bool cInputMgr::anyKeyPressed()
{
	for (BYTE keys = 0; keys < 256; keys++)
	{
		if (keysPressedBuffer[keys] == true)
		{
			return true;
		}
	}
	return false;
}
/*
=============================================================================
Clear the specified key press
=============================================================================
*/
void cInputMgr::clearKeyPress(int vkey)
{
	if (vkey < 256)
	{
		keysPressedBuffer[vkey] = false;
	}
}
/*
=============================================================================
Clear buffers, single or combined
=============================================================================
*/
void cInputMgr::clearBuffers(BYTE bufferToClear)
{
	if (bufferToClear & KEYS_DOWN_BUFFER)       // if clear keys down
	{
		for (int key = 0; key < 256; key++)
		{
			keysDownBuffer[key] = false;
		}
	}
	if (bufferToClear & KEYS_PRESSED_BUFFER)    // if clear keys pressed
	{
		for (int key = 0; key < 256; key++)
		{
			keysPressedBuffer[key] = false;
		}
	}
	if (bufferToClear & MOUSE_BUFFER)           // if clear mouse
	{
		mousePos.x = 0;
		mousePos.y = 0;
	}
}
/*
=============================================================================
Reads mouse screen position into mouseX, mouseY
=============================================================================
*/
void cInputMgr::mouseXY(LPARAM lParam)
{
	mousePos.x = LOWORD(lParam);
	mousePos.y = HIWORD(lParam);
}

glm::ivec2 cInputMgr::mouseXYDelta()
{
	return mousePos - mousePosOld;
}

void cInputMgr::resetMouseDelta()
{
	//mousePosOld = mousePos;
	mousePosOld = glm::ivec2(W_WIDTH/2, W_HEIGHT/2 - 12);
}

/*
=============================================================================
Save state of mouse button
=============================================================================
*/
void cInputMgr::setLeftMouseBtn(bool b)
{
	leftMouseBtn = b;
}
/*
=============================================================================
Save state of mouse button
=============================================================================
*/
void cInputMgr::setMiddleMouseBtn(bool b)
{
	middleMouseBtn = b;
}
/*
=============================================================================
Save state of mouse button
=============================================================================
*/
void cInputMgr::setRightMouseBtn(bool b)
{
	rightMouseBtn = b;
}
/*
=============================================================================
Return mouse X position
=============================================================================
*/
int  cInputMgr::getMouseXPos()
{
	return mousePos.x;
}
/*
=============================================================================
Return mouse Y position
=============================================================================
*/
int  cInputMgr::getMouseYPos()
{
	return mousePos.y;
}
/*
=============================================================================
Return state of left mouse button.
=============================================================================
*/
bool cInputMgr::getLeftMouseBtn()
{
	return leftMouseBtn;
}
/*
=============================================================================
Return state of middle mouse button.
=============================================================================
*/
bool cInputMgr::getMiddleMouseBtn()
{
	return middleMouseBtn;
}
/*
=============================================================================
Return state of right mouse button.
=============================================================================
*/
bool cInputMgr::getRightMouseBtn()
{
	return rightMouseBtn;
}

bool cInputMgr::getInputAction(std::string button)
{
	for (auto &iter : m_inputActions)
	{
		if (iter.name == button)
			return iter.state;
	}

	return false;
}

bool cInputMgr::getInputActionDown(std::string button)
{
	for (auto &iter : m_inputActions)
	{
		if (iter.name == button)
			return iter.state && !iter.stateOld;
	}

	return false;
}

bool cInputMgr::getInputActionUp(std::string button)
{
	for (auto &iter : m_inputActions)
	{
		if (iter.name == button)
			return !iter.state && iter.stateOld;
	}

	return false;
}

InputAction* cInputMgr::getInputActionState(std::string button)
{
	for (auto &iter : m_inputActions)
	{
		if (iter.name == button)
			return &iter;
	}

	return nullptr;
}

void cInputMgr::updateInputActions()
{
	for (auto &iter : m_inputActions)
	{
		for (auto &key : iter.keys)
		{
			iter.state = isKeyDown(key);
		}
		if (iter.state != iter.stateOld)
			iter.InputActionChange(iter.state);
	}
}

void cInputMgr::cleanInputActions()
{
	for (auto &iter : m_inputActions)
	{
		iter.stateOld = iter.state;
		iter.state = false;
	}
}

void cInputMgr::updateInputAxis()
{
	for (auto &iter : m_inputAxis)
	{
		float Pos = 0.0f;
		float Neg = 0.0f;

		for (auto &key : iter.keysPos)
		{
			if (isKeyDown(key)) Pos = 1;
		}

		for (auto &key : iter.keysNeg)
		{
			if (isKeyDown(key)) Neg = -1;
		}

		iter.state = Pos + Neg;
		if (iter.state != 0)
		{
			iter.InputAxisChange(iter.state);
		}
	}
}

float cInputMgr::getInputAxis(std::string name)
{
	for (auto &iter : m_inputAxis)
	{
		if (iter.name == name)
			return iter.state;
	}
	return 0;
}

InputAxis* cInputMgr::getInputAxisState(std::string name)
{
	for (auto &iter : m_inputAxis)
	{
		if (iter.name == name)
			return &iter;
	}

	return nullptr;
}

void cInputMgr::cleanInputAxis()
{
	for (auto &iter : m_inputAxis)
	{
		iter.state = 0.0f;
	}
}

