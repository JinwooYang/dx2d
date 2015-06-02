#include "DXUT.h"
#include "Repeat.h"
#include "Node.h"

USING_NS_DX2DX;

Repeat::Repeat()
{
}


Repeat::~Repeat()
{
	_Act->Release();
}

Repeat* Repeat::Create(int repeatTime, Action* act)
{
	auto repeat = new Repeat;
	repeat->Init(repeatTime, act);
	repeat->AutoRelease();

	return repeat;
}

void Repeat::Init(int repeatTime, Action* act)
{
	_MaxRepeatTime = repeatTime;
	_Act = act;
	_Act->Retain();
}

void Repeat::OnStartWithTarget(Node* const node)
{
	_CurRepeatTime = 0;
	_Act->StartWithTarget(node);
}

void Repeat::Run(Node* const node)
{
	_Act->Run(node);

	if (_Act->IsFinished())
	{
		++_CurRepeatTime;

		if (_CurRepeatTime == _MaxRepeatTime)
		{
			ActionFinish();
		}
		else
		{
			_Act->StartWithTarget(node);
		}
	}
}

Action* Repeat::Clone() const
{
	auto clone = Repeat::Create(this->_MaxRepeatTime, this->_Act->Clone());
	
	return clone;
}

Action* Repeat::Reverse() const
{
	auto reverse = Repeat::Create(this->_MaxRepeatTime, this->_Act->Reverse());

	return reverse;
}