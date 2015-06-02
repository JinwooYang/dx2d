#include "DXUT.h"
#include "dx2dxFunc.h"
#include <random>

int RandomInt(int min, int max)
{
	static std::random_device device;
	std::uniform_int_distribution<int> intRange(min, max);

	return intRange(device);
}

float RandomFloat(float min, float max)
{
	static std::random_device device;
	std::uniform_real_distribution<float> floatRange(min, max);

	return floatRange(device);
}

bool KEY_DOWN_ONCE(int vKey, bool *keyState)
{
	if (!*keyState && GetAsyncKeyState(vKey) & 0x8000)
	{
		*keyState = true;
		return true;
	}
	else if (!(GetAsyncKeyState(vKey) & 0x8000))
	{
		*keyState = false;
	}
	return false;
}

bool KEY_UP_ONCE(int vKey, bool *keyState)
{
	if (!*keyState && !(GetAsyncKeyState(vKey) & 0x8000))
	{
		*keyState = true;
		return true;
	}
	else if (GetAsyncKeyState(vKey) & 0x8000)
	{
		*keyState = false;
	}
	return false;
}

dx2dx::Point GET_MOUSE_POS()
{
	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(DXUTGetHWND(), &mousePos);

	return dx2dx::Point(mousePos.x, mousePos.y);
}

bool LBUTTON_DOWN_ONCE()
{
	static bool lBtnDown = false;

	if (!lBtnDown && DXUTIsMouseButtonDown(VK_LBUTTON))
	{
		lBtnDown = true;
		return true;
	}
	else if (!DXUTIsMouseButtonDown(VK_LBUTTON))
	{
		lBtnDown = false;
	}
	return false;
}

bool LBUTTON_UP_ONCE()
{
	static bool lBtnUp = false;

	if (!lBtnUp && !DXUTIsMouseButtonDown(VK_LBUTTON))
	{
		lBtnUp = true;
		return true;
	}
	else if (DXUTIsMouseButtonDown(VK_LBUTTON))
	{
		lBtnUp = false;
	}
	return false;
}

void GAME_SHUTDOWN()
{
	PostMessage(DXUTGetHWND(), WM_CLOSE, 0, 0);
}