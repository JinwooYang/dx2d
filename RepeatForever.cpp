#include "DXUT.h"
#include "RepeatForever.h"

USING_NS_DX2DX;

RepeatForever::RepeatForever()
{
}


RepeatForever::~RepeatForever()
{
	_Act->Release();
}


RepeatForever* RepeatForever::Create(Action* act)
{
	auto repForever = new RepeatForever;
	repForever->Init(act);
	repForever->AutoRelease();

	return repForever;
}


void RepeatForever::Init(Action* act)
{
	_Act = act;
	_Act->Retain();
}


void RepeatForever::OnStartWithTarget(Node* const node)
{
	_Act->StartWithTarget(node);
}


void RepeatForever::Run(Node* const node)
{
	_Act->Run(node);

	if (_Act->IsFinished())
	{
		_Act->StartWithTarget(node);
	}
}


Action* RepeatForever::Clone() const
{
	auto clone = RepeatForever::Create(_Act->Clone());
	return clone;
}


Action* RepeatForever::Reverse() const
{
	auto reverse = RepeatForever::Create(_Act->Reverse());
	return reverse;
}