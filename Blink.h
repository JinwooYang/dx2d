#pragma once
#include "Action.h"

NS_DX2DX
{

	class Blink
	: public Action
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(Blink);
		Blink(float duration, int blinkTime);
		~Blink();

		const float _Duration;
		const int _GoalBlinkTime;
		int _CurBlinkTime;

		const int _GoalFrame;
		int _PassFrame;

		bool _OrgVisible;

		virtual void OnStartWithTarget(Node* const node) override;

	public:
		virtual void Run(Node* const node);

		virtual Action* Clone() const override;
		virtual Action* Reverse() const override;

		static Blink* Create(float duration, int blinkTime)
		{
			auto blink = new Blink(duration, blinkTime);
			blink->AutoRelease();

			return blink;
		}
	};

}
