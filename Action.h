#pragma once
#include "Ref.h"

//Action�� ��� �Ҷ� ������ ��
//* Action������ InnerAction�� ����ϴ°�� ex : Repeat, Sequence, ...
//  �� InnerAction�� Retain�ϴ� ������ Create�Լ� ���ο��� �Ѵ�.
//  �ֳ��ϸ� ���� OnStartWithTarget �Լ� ���ο��� �� ��� �� �׼��� �ٸ� �׼���
//  InnerAction���� �� ��, Retain�� ��ø���� �� ���ɼ��� �ֱ� �����̴�.

NS_DX2DX
{
	class Node;

	class Action
		: public Ref
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(Action);

	private:
		bool _Finish;

	protected:
		Action();
		virtual ~Action();

		void ActionFinish() { _Finish = true; }

		virtual void OnStartWithTarget(Node * const node) = 0;

	public:
		void StartWithTarget(Node* const node)
		{
			_Finish = false;
			OnStartWithTarget(node);
		}

		virtual void Run(Node* const node) = 0;


		virtual Action* Clone() const = 0;
		virtual Action* Reverse() const = 0;

	public:
		bool IsFinished() { return _Finish; }
	};
}
