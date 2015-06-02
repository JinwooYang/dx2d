//#pragma once
//#define DIRECTINPUT_VERSION 0x0800
//#include <dinput.h>
//#include "dx2dxMacros.h"
//
//class Input
//{
//private:
//	SINGLETONE(Input)
//
//private:
//	IDirectInput8* m_directInput;
//	IDirectInputDevice8* m_keyboard;
//	IDirectInputDevice8* m_mouse;
//
//	unsigned char m_keyboardState[256];
//	DIMOUSESTATE m_mouseState;
//
//	int m_screenWidth, m_screenHeight;
//	int m_mouseX, m_mouseY;
//
//private:
//	bool ReadKeyboard();
//	bool ReadMouse();
//	void ProcessInput();
//
//public:
//	bool Init(DWORD keyCoopLevel, DWORD mouseCoopLevel);
//	void Shutdown();
//	bool Frame();
//
//	bool IsKeyPressed(int keyCode);
//	void GetMouseLocation(int&, int&);
//
//
//};
//
