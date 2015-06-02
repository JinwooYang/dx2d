#include "DXUT.h"
#include "Label.h"
#include "TTF.h"

USING_NS_DX2DX;

Label::Label(LPCWSTR fontFile, int size, LPCWSTR string, bool italic) :
_d3dxFont(nullptr),
_String(string),
_Italic(italic)
{
	auto returnNum = AddFontResourceEx(fontFile, FR_PRIVATE, 0);

	TTF ttf;
	ttf.Parse(fontFile);

	//ASSERT(returnNum == 0, "AddFontResourcesEx Failed!");

	D3DXCreateFont(DXUTGetD3D9Device(), size, 0, FW_BOLD, 1, _Italic,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, ttf.GetFontName().c_str(), &_d3dxFont);
}


Label::~Label()
{
	SAFE_RELEASE(_d3dxFont);
}


void Label::Draw(LPD3DXSPRITE d3dxSprite)
{
	if (!this->IsVisible()) return;

	RECT rt;

	auto pos = this->GetPosition();
	rt.left = pos.x;
	rt.top = pos.y;

	_d3dxFont->DrawText(d3dxSprite, _String.c_str(), -1, &rt, DT_CALCRECT, D3DCOLOR_XRGB(255,255,255));

	auto width = rt.right - rt.left;
	auto height = rt.bottom - rt.top;

	auto anchor = this->GetAnchorPoint();
	auto point = Point(width * anchor.x, height * anchor.y);

	rt.left -= point.x;
	rt.top -= point.y;

	_d3dxFont->DrawText(d3dxSprite, _String.c_str(), -1, &rt, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}


Label* Label::Create(LPCWSTR fontFile, int size, LPCWSTR string, bool italic)
{
	auto label = new Label(fontFile, size, string, italic);
	label->AutoRelease();

	return label;
}


void Label::SetString(LPCWSTR string)
{
	_String = string;
}