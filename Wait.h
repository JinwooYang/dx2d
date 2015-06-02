#pragma once
#include "Action.h"

NS_DX2DX
{
	class Wait
	: public Action
	{
	private:
		float _Duration;
		int _CurFrame;

		Wait(float duration);
		~Wait();
		DISALLOW_COPY_AND_ASSIGN(Wait);

	public:
		static Wait* Create(float duration);

		virtual void OnStartWithTarget(Node* const node) override;
		virtual void Run(Node* const node) override;

		virtual Action* Clone() const override;
		virtual Action* Reverse() const override;
	};
}
