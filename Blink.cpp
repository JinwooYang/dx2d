#include "DXUT.h"
#include "Blink.h"
#include "Node.h"

USING_NS_DX2DX;

Blink::Blink(float duration, int blinkTime) :
_Duration(duration),
_GoalBlinkTime(blinkTime),
_CurBlinkTime(0),
_GoalFrame(duration * 60 / (blinkTime * 2)),
_PassFrame(0),
_OrgVisible(true)
{
}


Blink::~Blink()
{
}


void Blink::OnStartWithTarget(Node* const node)
{
	this->_OrgVisible = node->IsVisible();
	node->SetVisible(!_OrgVisible);
}


void Blink::Run(Node* const node)
{
	if (++_PassFrame >= _GoalFrame)
	{
		auto visible = node->IsVisible();
		node->SetVisible(!visible);
		_PassFrame = 0;
		if (_OrgVisible == !visible)
		{
			if (++_CurBlinkTime == _GoalBlinkTime)
			{
				ActionFinish();
			}
		}
	}
}


Action* Blink::Clone() const
{
	auto blink = Blink::Create(_Duration, _GoalBlinkTime);
	return blink;
}


Action* Blink::Reverse() const
{
	return (this->Clone());
}