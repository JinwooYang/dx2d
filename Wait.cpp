#include "DXUT.h"
#include "Wait.h"
#include "Node.h"

USING_NS_DX2DX;

Wait::Wait(float duration) :
_Duration(duration),
_CurFrame(0)
{
}


Wait::~Wait()
{
}

Wait* Wait::Create(float duration)
{
	auto wait = new Wait(duration);
	wait->AutoRelease();

	return wait;
}

void Wait::OnStartWithTarget(Node* const node)
{
	_CurFrame = 0;
}

void Wait::Run(Node* const node)
{
	if (_CurFrame++ >= _Duration * 60)
	{
		ActionFinish();
	}
}

Action* Wait::Clone() const
{
	auto clone = Wait::Create(this->_Duration);

	return clone;
}

Action* Wait::Reverse() const
{
	return this->Clone();
}
