#include "DXUT.h"
#include "Sequence.h"

USING_NS_DX2DX;

Sequence::Sequence()
{
}


Sequence::~Sequence()
{
	for (auto act : _ActionVec)
	{
		act->Release();
	}
}

Sequence* Sequence::Create(std::initializer_list<Action*> list)
{
	auto seq = new Sequence;
	seq->Init(list);
	seq->AutoRelease();

	return seq;
}

Sequence* Sequence::Create(std::vector<Action*> actionVec)
{
	auto seq = new Sequence;
	seq->Init(actionVec);
	seq->AutoRelease();

	return seq;
}

void Sequence::Init(std::initializer_list<Action*> list)
{
	_ActionVec = list;

	for (auto act : _ActionVec)
		act->Retain();
}

void Sequence::Init(std::vector<Action*> actionVec)
{
	_ActionVec = actionVec;

	for (auto act : _ActionVec)
		act->Retain();
}

void Sequence::OnStartWithTarget(Node* node)
{
	_CurSeq = 0;
	_ActionVec[0]->StartWithTarget(node);
	//for (auto act : _ActionVec)
	//{
	//	act->StartWithTarget(node);
	//}
}

void Sequence::Run(Node* node)
{
	_ActionVec[_CurSeq]->Run(node);
	if (_ActionVec[_CurSeq]->IsFinished())
	{
		if (++_CurSeq < _ActionVec.size())
		{
			_ActionVec[_CurSeq]->StartWithTarget(node);
		}
		else
		{
			ActionFinish();
		}
	}
}

Action* Sequence::Clone() const
{
	std::vector<Action*> actionVec;

	for (auto act : _ActionVec)
	{
		actionVec.push_back(act->Clone());
	}

	auto clone = Sequence::Create(actionVec);

	return clone;
}

Action* Sequence::Reverse() const
{
	std::vector<Action*> actionVec;

	for (auto act : _ActionVec)
	{
		actionVec.push_back(act->Reverse());
	}

	auto reverse = Sequence::Create(actionVec);

	return reverse;
}