#include "DXUT.h"
#include "Game.h"
#include "TitleScene.h"
#include "AppDelegate.h"
#include "TextureManager.h"
#include <time.h>

USING_NS_DX2DX;

Game::Game()
{
	LOG("Game is Started!\n");
}


Game::~Game()
{
	LOG("Game is Ended!\n");
}

bool Game::CheckLFH()
{
	ULONG  HeapFragValue = 2;


	if (HeapSetInformation(GetProcessHeap(),
		HeapCompatibilityInformation,
		&HeapFragValue,
		sizeof(HeapFragValue)))
	{
		return true;
	}
	return false;
}

Game* Game::GetInstance()
{
	static Game instance;

	return &instance;
}

void Game::Init()
{
	if (CheckLFH())
	{
		LOG("Use Low Fragmentation Heap\n");
	}

	_pD3D = DXUTGetD3D9Device();

	_AutoReleasePool = AutoReleasePool::GetInstance();
	_Director = Director::GetInstance();
	_ActionMgr = ActionManager::GetInstance();
	//_Input = Input::GetInstance();

	//_Input->Init(DISCL_FOREGROUND | DISCL_EXCLUSIVE,
	//			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	_App.AppLaunching();

	srand((unsigned int)time(nullptr));
}

void Game::Update(double fTime) const
{
	//static double oldTime = fTime;
	//if (fTime - oldTime > 5)
	//{
	//	oldTime = fTime;
	//}

	//_Input->Frame();
	_ActionMgr->Update();
	_Director->UpdateCurScene();
	_AutoReleasePool->Clear();
}

void Game::Render() const
{
	HRESULT hr;
	V(_pD3D->Clear(0, NULL, D3DCLEAR_TARGET /*| D3DCLEAR_ZBUFFER*/, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0));

	// Render the scene
	if (SUCCEEDED(_pD3D->BeginScene()))
	{
		_Director->DrawCurScene();
		V(_pD3D->EndScene());
	}
}

void Game::Release()
{
	Director::DestroyInstance();
	AutoReleasePool::DestroyInstance();
	TextureManager::DestroyInstance();
	ActionManager::DestroyInstance();
	//Input::DestroyInstance();
}

void Game::GetMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
	bool* pbNoFurtherProcessing, void* pUserContext)
{
	_Director->MsgProc(hWnd, uMsg, wParam, lParam,
						pbNoFurtherProcessing, pUserContext);
}

void Game::OnResetDevice() const
{
	_Director->CreateD3DXSprite();
}

void Game::OnLostDevice() const
{
	_Director->ReleaseD3DXSprite();
}
