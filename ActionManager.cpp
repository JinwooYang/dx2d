#include "DXUT.h"
#include "ActionManager.h"
#include "Action.h"
#include "Node.h"

USING_NS_DX2DX;
SINGLETONE_INSTANCE_INIT(ActionManager, nullptr);

ActionManager::ActionManager()
{
	_ActionPool.reserve(50);
}


ActionManager::~ActionManager()
{
}


void ActionManager::AddAction(Action* const act, Node* const node)
{
	act->StartWithTarget(node);
	act->Retain();
	_ActionPool.push_back(ActionData{act, node});
}

void ActionManager::Update()
{
	for (auto iter = _ActionPool.begin(); iter != _ActionPool.end();)
	{
		auto actData = *iter;

		actData.act->Run(actData.node);

		if (actData.act->IsFinished())
		{
			actData.node->ActionFinish();
			actData.act->Release();
			iter = _ActionPool.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void ActionManager::DeleteNodeAction(Node* node)
{
	for (auto iter = _ActionPool.begin(); iter != _ActionPool.end();)
	{
		auto actData = *iter;

		if (actData.node == node)
		{
			actData.node->ActionFinish();
			actData.act->Release();
			iter = _ActionPool.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void ActionManager::DeleteAllAction()
{
	for (auto iter = _ActionPool.begin(); iter != _ActionPool.end();)
	{
		auto actData = *iter;

		actData.act->Release();
		iter = _ActionPool.erase(iter);
	}
}