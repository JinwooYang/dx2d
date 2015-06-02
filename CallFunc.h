#pragma once
#include "Action.h"
#include <functional>

NS_DX2DX
{
	class CallFunc
		: public dx2dx::Action
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(CallFunc);
		CallFunc();
		~CallFunc();

	private:
		std::function<void()> _Func;

		void Init(std::function<void()> func);

		virtual void OnStartWithTarget(Node* const node) override {}

	public:
		static CallFunc* Create(std::function<void()> func);

		virtual void Run(Node* const node) override;

		virtual Action* Clone() const override;
		virtual Action* Reverse() const override;
	};
}