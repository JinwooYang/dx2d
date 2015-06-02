#pragma once
#include "Action.h"

NS_DX2DX
{
	class Repeat
	: public dx2dx::Action
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(Repeat);
		Repeat();
		~Repeat();

	private:
		int _MaxRepeatTime, _CurRepeatTime;
		Action* _Act;

		void Init(int repeatTime, Action* act);

		virtual void OnStartWithTarget(Node* const node) override;

	public:
		static Repeat* Create(int repeatTime, Action* act);

		virtual void Run(Node* const node) override;

		virtual Action* Clone() const override;
		virtual Action* Reverse() const override;
	};
}
