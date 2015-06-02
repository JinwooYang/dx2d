#pragma once
#include "Action.h"

NS_DX2DX
{

	class RepeatForever
		: public Action
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(RepeatForever);

		RepeatForever();
		~RepeatForever();

	private:
		Action* _Act;

		virtual void OnStartWithTarget(Node* const node) override;

		void Init(Action* act);

	public:
		static RepeatForever* Create(Action* act);

		virtual void Run(Node* const node) override;

		virtual Action* Clone() const override;
		virtual Action* Reverse() const override;
	};

}