#include "DXUT.h"
#include "TintTo.h"
#include "Node.h"

USING_NS_DX2DX;

TintTo::TintTo(float duration, Color4F color) :
_Duration(duration),
_TargetColor(color)
{
}


TintTo::~TintTo()
{
}

TintTo* TintTo::Create(float duration, Color4F color)
{
	auto tintTo = new TintTo(duration, color);
	tintTo->AutoRelease();

	return tintTo;
}

void TintTo::OnStartWithTarget(Node* const node)
{
	_OrgColor = node->GetColor();
	float fps = _Duration * 60.0f;
	_ColorVal = Color4F((_TargetColor.r - _OrgColor.r) / fps,
						(_TargetColor.g - _OrgColor.g) / fps,
						(_TargetColor.b - _OrgColor.b) / fps,
						(_TargetColor.a - _OrgColor.a) / fps);
}

void TintTo::Run(Node* const node)
{
	node->TintBy(_ColorVal);
	auto nodeColor = node->GetColor();

	if ((_OrgColor.a < _TargetColor.a && nodeColor.a > _TargetColor.a) ||
		(_OrgColor.a > _TargetColor.a && nodeColor.a < _TargetColor.a))
	{
		nodeColor.a = _TargetColor.a;
	}

	if ((_OrgColor.r < _TargetColor.r && nodeColor.r > _TargetColor.r) ||
		(_OrgColor.r > _TargetColor.r && nodeColor.r < _TargetColor.r))
	{
		nodeColor.r = _TargetColor.r;
	}

	if ((_OrgColor.g < _TargetColor.g && nodeColor.g > _TargetColor.g) ||
		(_OrgColor.g > _TargetColor.g && nodeColor.g < _TargetColor.g))
	{
		nodeColor.g = _TargetColor.g;
	}

	if ((_OrgColor.b < _TargetColor.b && nodeColor.b > _TargetColor.b) ||
		(_OrgColor.b > _TargetColor.b && nodeColor.b < _TargetColor.b))
	{
		nodeColor.b = _TargetColor.b;
	}

	node->SetColor(nodeColor);

	if (nodeColor == _TargetColor)
	{
		ActionFinish();
	}

}

Action* TintTo::Clone() const
{
	auto clone = TintTo::Create(this->_Duration, this->_TargetColor);

	return clone;
}

Action* TintTo::Reverse() const
{
	auto reverse = TintTo::Create(this->_Duration, this->_OrgColor);

	return reverse;
}