#include "DXUT.h"
//#include "Input.h"
//#include "dx2dxMacros.h"
//
//SINGLETONE_INSTANCE_INIT(Input, nullptr);
//
//Input::Input()
//{
//	m_directInput = nullptr;
//	m_keyboard = nullptr;
//	m_mouse = nullptr;
//}
//
//
//Input::~Input()
//{
//	Shutdown();
//}
//
//bool Input::Init(DWORD keyCoopLevel, DWORD mouseCoopLevel)
//{
//	HRESULT hr;
//
//	// Store the screen size which will be used for positioning the mouse cursor.
//	m_screenWidth = WINDOW_X;
//	m_screenHeight = WINDOW_Y;
//
//	// Initialize the location of the mouse on the screen.
//	m_mouseX = 0;
//	m_mouseY = 0;
//
//	// Initialize the main direct input interface.
//	V(DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, nullptr));
//
//	// Initialize the direct input interface for the keyboard.
//	V(m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, nullptr));
//
//	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
//	V(m_keyboard->SetDataFormat(&c_dfDIKeyboard));
//
//	// Set the cooperative level of the keyboard to not share with other programs.
//	V(m_keyboard->SetCooperativeLevel(DXUTGetHWND(), keyCoopLevel));
//
//	DIPROPDWORD dipdw;
//
//	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
//	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
//	dipdw.diph.dwObj = 0;
//	dipdw.diph.dwHow = DIPH_DEVICE;
//	dipdw.dwData = 0; // 0;
//
//	V(m_keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph));
//
//	// Now acquire the keyboard.
//	m_keyboard->Acquire();
//
//	// Initialize the direct input interface for the mouse.
//	V(m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, nullptr));
//
//	// Set the data format for the mouse using the pre-defined mouse data format.
//	V(m_mouse->SetDataFormat(&c_dfDIMouse));
//
//	// Set the cooperative level of the mouse to share with other programs.
//	V(m_mouse->SetCooperativeLevel(DXUTGetHWND(), mouseCoopLevel));
//
//	// Acquire the mouse.
//	m_mouse->Acquire();
//
//	return true;
//}
//
//void Input::Shutdown()
//{
//	// Release the mouse.
//	if (m_mouse)
//	{
//		m_mouse->Unacquire();
//		m_mouse->Release();
//		m_mouse = nullptr;
//	}
//
//	// Release the keyboard.
//	if (m_keyboard)
//	{
//		m_keyboard->Unacquire();
//		m_keyboard->Release();
//		m_keyboard = nullptr;
//	}
//
//	// Release the main interface to direct input.
//	SAFE_RELEASE(m_directInput)
//
//	return;
//}
//
//bool Input::Frame()
//{
//	// Read the current state of the keyboard.
//	if(!ReadKeyboard())
//		return false;
//
//	// Read the current state of the mouse.
//	if(!ReadMouse())
//		return false;
//
//	// Process the changes in the mouse and keyboard.
//	ProcessInput();
//
//	return true;
//}
//
//bool Input::ReadKeyboard()
//{
//	HRESULT hr;
//
//	// Read the keyboard device.
//	hr = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
//	if (FAILED(hr))
//	{
//		// If the keyboard lost focus or was not acquired then try to get control back.
//		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
//			m_keyboard->Acquire();
//		else
//			return false;
//	}
//
//	return true;
//}
//
//bool Input::ReadMouse()
//{
//	HRESULT hr;
//
//	// Read the mouse device.
//	hr = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
//
//	if (FAILED(hr))
//	{
//		// If the mouse lost focus or was not acquired then try to get control back.
//		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
//			m_mouse->Acquire();
//		else
//			return false;
//	}
//
//	return true;
//}
//
//void Input::ProcessInput()
//{
//	// Update the location of the mouse cursor based on the change of the mouse location during the frame.
//	m_mouseX += m_mouseState.lX;
//	m_mouseY += m_mouseState.lY;
//
//	// Ensure the mouse location doesn't exceed the screen width or height.
//	if (m_mouseX < 0)  { m_mouseX = 0; }
//	if (m_mouseY < 0)  { m_mouseY = 0; }
//
//	if (m_mouseX > m_screenWidth)  { m_mouseX = m_screenWidth; }
//	if (m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }
//
//	return;
//}
//
//bool Input::IsKeyPressed(int keyCode)
//{
//	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
//	if (m_keyboardState[keyCode] & 0x80)
//	{
//		return true;
//	}
//
//	return false;
//}
//
//void Input::GetMouseLocation(int& mouseX, int& mouseY)
//{
//	mouseX = m_mouseX;
//	mouseY = m_mouseY;
//	return;
//}
//
//
