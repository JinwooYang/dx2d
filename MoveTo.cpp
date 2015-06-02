#include "DXUT.h"
#include "MoveTo.h"
#include "Node.h"

USING_NS_DX2DX;

MoveTo::MoveTo()
{
}


MoveTo::~MoveTo()
{
}

MoveTo* MoveTo::Create(float duration, Point pos)
{
	auto moveTo = new MoveTo;
	moveTo->Init(duration, pos);
	moveTo->AutoRelease();

	return moveTo;
}

void MoveTo::Init(float duration, Point pos)
{
	_Duration = duration;
	_EndPos = pos;
}

void MoveTo::OnStartWithTarget(Node* const node)
{
	_StartPos = node->GetPosition();

	_MoveRight = (_EndPos.x - _StartPos.x > 0);
	_MoveDown = (_EndPos.y - _StartPos.y > 0);

	float fps;

	if (_Duration <= 0.0f)
		fps = 1;
	else
		fps = _Duration * 60;

	auto dist = Point(_EndPos.x - _StartPos.x, _EndPos.y - _StartPos.y);

	_MoveVal.x = dist.x / fps;
	_MoveVal.y = dist.y / fps;
}

void MoveTo::Run(Node* const node)
{
	node->MoveBy(_MoveVal);

	auto nodePos = node->GetPosition();

	if ((_MoveRight && _EndPos.x <= nodePos.x) ||
		(!_MoveRight && _EndPos.x >= nodePos.x))
	{
		node->SetPositionX(_EndPos.x);
	}

	if ((_MoveDown && _EndPos.y <= nodePos.y) ||
		(!_MoveDown && _EndPos.y >= nodePos.y))
	{
		node->SetPositionY(_EndPos.y);
	}

	if (_EndPos == node->GetPosition())
	{
		ActionFinish();
	}

}

Action* MoveTo::Clone() const
{
	auto clone = MoveTo::Create(this->_Duration, this->_EndPos);

	return clone;
}

Action* MoveTo::Reverse() const
{
	auto reverse = MoveTo::Create(this->_Duration, this->_StartPos);

	return reverse;
}