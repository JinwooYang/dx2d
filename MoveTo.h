#pragma once
#include "Action.h"
#include "dx2dxStruct.h"

NS_DX2DX
{
	class MoveTo
		: public dx2dx::Action
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(MoveTo);
		MoveTo();
		~MoveTo();

	private:
		dx2dx::Point _StartPos, _EndPos, _MoveVal;
		float _Duration;
		bool _MoveRight, _MoveDown;

		void Init(float duration, dx2dx::Point pos);

		virtual void OnStartWithTarget(Node* const node) override;
	
	public:
		static MoveTo* Create(float duration, dx2dx::Point pos);

		virtual void Run(Node* const node) override;

		virtual Action* Clone() const override;
		virtual Action* Reverse() const override;
	};
}
