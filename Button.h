#pragma once
#include "Sprite.h"
#include <functional>

NS_DX2DX
{
	class Button
	: public Sprite
	{
		typedef std::function < void(Button*) > BtnCB;

	private:
		DISALLOW_COPY_AND_ASSIGN(Button);
		Button(LPCWSTR fileDir, BtnCB clickedCB, BtnCB updateCB);
		~Button();

		bool _Active;
		bool _Selected, _Clicked, _Down;

		BtnCB _ClickedCB, _UpdateCB;

	public:
		static Button* Create(LPCWSTR fileDir,
			BtnCB clickedCB = nullptr,
			BtnCB updateCB = nullptr);

		virtual void EarlyUpdate() override;

		void SetActive(bool active) { _Active = active; };

		bool IsActive() { return _Active; };
		bool IsSelected() { return _Selected; };
		bool IsClicked() { return _Clicked; };
		bool IsDown() { return _Down; };
	};
}
