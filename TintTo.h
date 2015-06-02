#pragma once
#include "Action.h"
#include "dx2dxStruct.h"

NS_DX2DX
{
	class TintTo
	: public Action
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(TintTo);
		TintTo(float duration, Color4F color);
		~TintTo();

	private:
		Color4F _OrgColor, _TargetColor, _ColorVal;
		float _Duration;

	public:
		static TintTo* Create(float duration, Color4F color);

		virtual void OnStartWithTarget(Node* const node) override;
		virtual void Run(Node* const node) override;

		virtual Action* Clone() const override;
		virtual Action* Reverse() const override;
	};
}
