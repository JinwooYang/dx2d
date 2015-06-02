#pragma once
#include "dx2dxMacros.h"
#include <vector>

NS_DX2DX
{
	class Action;
	class Node;

	struct ActionData
	{
		Action *act;
		Node *node;
	};


	class ActionManager
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(ActionManager);
		SINGLETONE(ActionManager);

	private:
		std::vector<ActionData> _ActionPool;

	public:
		void AddAction(Action* const act, Node* const node);
		void Update();

		void DeleteNodeAction(Node* node);
		void DeleteAllAction();
	};
}
