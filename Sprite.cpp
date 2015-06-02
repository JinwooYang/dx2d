#include "DXUT.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Director.h"
#include "UserDefines.h"

USING_NS_DX2DX;

Sprite::Sprite(LPCWSTR fileDir) :
_Texture(TextureManager::GetInstance()->GetTexture(fileDir)),
//_d3dColor(D3DCOLOR_XRGB(255, 255, 255)),
_wFrame(1),
_hFrame(1),
_AnimateTime(0),
_NowFrame(0),
_FrameCnt(1),
_AnimationCnt(0),
_Animate(false)
{
	D3DSURFACE_DESC desc;
	_Texture->GetLevelDesc(0, &desc);

	SetSize(desc.Width, desc.Height);
	_CutWidth = desc.Width;
	_CutHeight = desc.Height;

	SetAnchorPoint(Point::ANCHOR_MIDDLE);

	SetRect(&_SrcRect, 0, 0, desc.Width, desc.Height);
	SetBoundingBox();
}

Sprite::~Sprite()
{
}

Sprite* Sprite::Create(LPCWSTR fileDir)
{
	auto sprite = new Sprite(fileDir);
	sprite->AutoRelease();

	return sprite;
}

//void Sprite::SetColor(D3DCOLOR color)
//{
//	_d3dColor = color;
//}
//
//D3DCOLOR Sprite::GetColor() const
//{
//	return _d3dColor;
//}
//
//void Sprite::Tint(D3DCOLOR color)
//{
//	_d3dColor += color;
//}

void Sprite::SetAnimation(AnimData animData)
{
	SetAnimation(animData.wFrame, animData.hFrame,
				animData.cutWidth, animData.cutHeight,
				animData.animateTime, animData.frameCnt);
}

void Sprite::SetAnimation(int wFrame, int hFrame, float cutWidth, float cutHeight, clock_t animateTime, int frameCnt)
{
	_Animate = true;
	_wFrame = wFrame;
	_hFrame = hFrame;
	SetSize(cutWidth, cutHeight);
	_CutWidth = cutWidth;
	_CutHeight = cutHeight;
	_AnimateTime = animateTime;
	_FrameCnt = frameCnt;

	_CurTime = clock();

	SetRect(&_SrcRect, 0, 0, cutWidth, cutHeight);
	SetAnchorPoint(Point::ANCHOR_MIDDLE);
}

void Sprite::Animation()
{
	if (clock() - _CurTime > _AnimateTime)
	{
		_CurTime = clock();

		auto left = _NowFrame % _wFrame * _CutWidth;
		auto top = _NowFrame / _wFrame * _CutHeight;
		SetRect(&_SrcRect, left, top, left + _CutWidth, top + _CutHeight);

		if (++_NowFrame >= _FrameCnt)
		{
			_NowFrame = 0;
			++_AnimationCnt;
		}
	}
}

int Sprite::GetAnimationCnt()
{
	return _AnimationCnt;
}

void Sprite::Draw(LPD3DXSPRITE d3dxSprite)
{
	if (!IsVisible()) return;

	if (_Animate)
		Animation();

	static auto director = Director::GetInstance();
	auto viewPos = GetWorldPosition();
	auto center = GetCenterPoint().GetVector3();
	auto scale = GetScale();

	viewPos.x -= director->GetCameraPosX() - WINDOW_X / 2;
	viewPos.y -= director->GetCameraPosY() - WINDOW_Y / 2;


	D3DXMATRIXA16 Mat;
	D3DXMatrixTransformation2D(&Mat, nullptr, 0.0f, &scale, nullptr, D3DXToRadian(GetRotAngle()), &viewPos);
	d3dxSprite->SetTransform(&Mat);

	Color4F color = GetColor();
	d3dxSprite->Draw(_Texture, &_SrcRect, &center, nullptr, GetD3DColor());

	D3DXMatrixIdentity(&Mat);
	d3dxSprite->SetTransform(&Mat);

	Node::Draw(d3dxSprite);
}