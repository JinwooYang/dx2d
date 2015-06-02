#include "DXUT.h"
#include "MoveBy.h"
#include "Node.h"

USING_NS_DX2DX;

MoveBy::MoveBy()
{
}


MoveBy::~MoveBy()
{
}

MoveBy* MoveBy::Create(float duration, Point pos)
{
	auto moveBy = new MoveBy;
	moveBy->Init(duration, pos);
	moveBy->AutoRelease();

	return moveBy;
}

void MoveBy::Init(float duration, Point pos)
{
	_Duration = duration;
	_EndPos = pos;
}

void MoveBy::OnStartWithTarget(Node* node)
{
	_StartPos = node->GetPosition();
	_Dest = _EndPos + _StartPos;

	_MoveRight = (_Dest.x - _StartPos.x > 0);
	_MoveDown = (_Dest.y - _StartPos.y > 0);

	float fps;

	if (_Duration <= 0.0f)
		fps = 1;
	else
		fps = _Duration * 60;

	auto dist = Point(_Dest.x - _StartPos.x, _Dest.y - _StartPos.y);

	_MoveVal.x = dist.x / fps;
	_MoveVal.y = dist.y / fps;
}

void MoveBy::Run(Node* node)
{
	node->MoveBy(_MoveVal);

	auto nodePos = node->GetPosition();

	if ((_MoveRight && _Dest.x <= nodePos.x) ||
		(!_MoveRight && _Dest.x >= nodePos.x))
	{
		node->SetPositionX(_Dest.x);
	}

	if ((_MoveDown && _Dest.y <= nodePos.y) ||
		(!_MoveDown && _Dest.y >= nodePos.y))
	{
		node->SetPositionY(_Dest.y);
	}

	if (_Dest == node->GetPosition())
	{
		ActionFinish();
	}

}

Action* MoveBy::Clone() const
{
	auto clone = MoveBy::Create(this->_Duration, this->_EndPos);

	return clone;
}

Action* MoveBy::Reverse() const
{
	auto reverse = MoveBy::Create(this->_Duration, this->_StartPos);

	return reverse;
}