#pragma once
#include "Action.h"
#include "dx2dxStruct.h"

NS_DX2DX
{
	class MoveBy
		: public dx2dx::Action
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(MoveBy);
		MoveBy();
		~MoveBy();

	private:
		dx2dx::Point _StartPos, _EndPos, _Dest, _MoveVal;
		float _Duration;
		bool _MoveRight, _MoveDown;

		void Init(float duration, dx2dx::Point pos);

		virtual void OnStartWithTarget(Node* const node) override;

	public:
		static MoveBy* Create(float duration, dx2dx::Point pos);

		virtual void Run(Node* const node) override;

		virtual Action* Clone() const override;
		virtual Action* Reverse() const override;
	};
}