#pragma once
#include "Node.h"
#include "AutoReleasePool.h"
#include "Director.h"
#include <time.h>
#include "Input.h"
#include "ActionManager.h"
#include "AppDelegate.h"

NS_DX2DX
{
	class Game
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(Game);
		Game();
		~Game();

	private:
		LPDIRECT3DDEVICE9 _pD3D;
		AutoReleasePool *_AutoReleasePool;
		Director *_Director;
		ActionManager *_ActionMgr;
		AppDelegate _App;
		//Input *_Input;

		bool CheckLFH();

	public:
		static Game* GetInstance();

		void Init();
		void Update(double fTime) const;
		void Render() const;
		void Release();

		void GetMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
					bool* pbNoFurtherProcessing, void* pUserContext);

		void OnResetDevice() const;
		void OnLostDevice() const;
	};
}
