#pragma once
#include "dx2dx.h"

NS_DX2DX
{
	class Label
	: public Node
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(Label);
		Label(LPCWSTR fontFile, int size, LPCWSTR string, bool italic);
		~Label();

		LPD3DXFONT _d3dxFont;
		std::wstring _String;
		bool _Italic;

	protected:
		virtual void Draw(LPD3DXSPRITE d3dxSprite) override;

	public:
		static Label* Create(LPCWSTR fontFile, int size, LPCWSTR string, bool italic = false);

		void SetString(LPCWSTR string);
	};
}
