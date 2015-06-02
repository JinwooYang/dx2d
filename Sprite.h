#pragma once
#include "Node.h"
#include "dx2dxMacros.h"
#include <time.h>

NS_DX2DX
{
	class Sprite
		: public Node
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(Sprite);

	protected:
		Sprite(LPCWSTR fileDir);
		~Sprite();

	private:
		LPDIRECT3DTEXTURE9 _Texture;
		RECT _SrcRect;
		int _wFrame, _hFrame, _FrameCnt, _NowFrame;
		float _CutWidth, _CutHeight;
		clock_t _AnimateTime, _CurTime;
		int _AnimationCnt;
		bool _Animate;

	public:
		static Node* Create() = delete;
		static Sprite* Create(LPCWSTR fileDir);

	public:
		void SetAnimation(AnimData animData);
		void SetAnimation(int wFrame, int hFrame, float cutWidth, float cutHeight, clock_t animateTime, int frameCnt);
	private:
		void Animation();

	public:
		int GetAnimationCnt();

	private:
		void Draw(LPD3DXSPRITE d3dxSprite) override;
	};
}