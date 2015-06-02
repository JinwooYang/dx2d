#pragma once
#include "Scene.h"
#include "dx2dxMacros.h"
#include <stack>

NS_DX2DX
{
	class Director final
	{
		friend class Game;
	private:
		DISALLOW_COPY_AND_ASSIGN(Director);
		Director();
		~Director();

	public:
		static Director* GetInstance();
	private:
		static void DestroyInstance();

	private:
		static Director *_Instance;
		std::stack<Scene*> _SceneStack;
		LPD3DXSPRITE _d3dxSprite;

		Point _CameraPos;

		bool _NeedToReplaceScene, _NeedToCleanUpTexture;

		Scene* _ChangeScene;

		void NowReplaceScene();

	public:
		void RunWithScene(Scene* const scene);

		void PushScene(Scene* const scene);
		void PopScene();

		//함수호출시 즉시 씬이 변경되지않고 현재 씬의 Update가 끝난 뒤 변경된다.
		void ReplaceScene(Scene* const scene, bool cleanUpTexturePool = false);

		void UpdateCurScene();
		void DrawCurScene() const;

		void SetCameraPos(Point const &pos);
		void SetCameraPos(float x, float y);
		void SetCameraPosX(float x);
		void SetCameraPosY(float y);

		Point GetCameraPos() const;
		float GetCameraPosX() const;
		float GetCameraPosY() const;

		Rect GetCameraBox() const;

		void MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
			bool* pbNoFurtherProcessing, void* pUserContext);

	private:
		void CreateD3DXSprite();
		void ReleaseD3DXSprite();
	public:
		LPD3DXSPRITE GetD3DXSprite() const;
	};
}
