#include "DXUT.h"
#include "Button.h"
#include "dx2dxFunc.h"

USING_NS_DX2DX;

#define SAFE_CALLBACK(callback) do{if((callback)) (callback)(this);}while(0)

Button::Button(LPCWSTR fileDir,
	BtnCB clickedCB,
	BtnCB updateCB) :
Sprite(fileDir),
_Active(true),
_Selected(false),
_Down(false),
_Clicked(false),
_ClickedCB(clickedCB),
_UpdateCB(updateCB)
{
}


Button::~Button()
{
}

Button* Button::Create(LPCWSTR fileDir, BtnCB clickedCB, BtnCB selectedCB)
{
	auto btn = new Button(fileDir, clickedCB, selectedCB);
	btn->AutoRelease();

	return btn;
}

void Button::EarlyUpdate()
{
	if (!_Active) return;

	Point mousePos = GET_MOUSE_POS();
	Rect myBox = this->GetBoundingBox();

	if (myBox.ContainsPoint(mousePos))
	{
		_Selected = true;

		//if (LBUTTON_DOWN_ONCE())
		if (DXUTIsMouseButtonDown(VK_LBUTTON))
		{
			_Down = true;
		}
		if (_Down && LBUTTON_UP_ONCE())
		{
			_Down = false;
			_Clicked = true;
			SAFE_CALLBACK(_ClickedCB);
		}
	}
	else
	{
		_Selected = false;
		_Down = false;
		_Clicked = false;
	}

	SAFE_CALLBACK(_UpdateCB);

	Node::EarlyUpdate();
}