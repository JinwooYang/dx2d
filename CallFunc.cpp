#include "DXUT.h"
#include "CallFunc.h"
#include "Node.h"

USING_NS_DX2DX;

CallFunc::CallFunc()
{
}

CallFunc::~CallFunc()
{
}

CallFunc* CallFunc::Create(std::function<void()> func)
{
	auto callFunc = new CallFunc;
	callFunc->Init(func);
	callFunc->AutoRelease();

	return callFunc;
}

void CallFunc::Init(std::function<void()> func)
{
	_Func = func;
}

void CallFunc::Run(Node* const node)
{
	_Func();
	ActionFinish();
}

Action* CallFunc::Clone() const
{
	auto clone = CallFunc::Create(this->_Func);

	return clone;
}

Action* CallFunc::Reverse() const
{
	return this->Clone();
}