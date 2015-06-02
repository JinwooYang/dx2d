#pragma once
#include "Ref.h"

//Action을 상속 할때 주의할 점
//* Action내에서 InnerAction을 사용하는경우 ex : Repeat, Sequence, ...
//  그 InnerAction을 Retain하는 시점은 Create함수 내부여야 한다.
//  왜냐하면 만약 OnStartWithTarget 함수 내부에서 할 경우 그 액션이 다른 액션의
//  InnerAction으로 들어갈 때, Retain이 중첩으로 될 가능성이 있기 때문이다.

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
