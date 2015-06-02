#include "DXUT.h"
#include "Director.h"
#include "Camera.h"
#include "UserDefines.h"
#include "TextureManager.h"

USING_NS_DX2DX;

SINGLETONE_INSTANCE_INIT(Director, nullptr);

Director::Director() :
_CameraPos(Point(WINDOW_X / 2, WINDOW_Y / 2)),
_NeedToReplaceScene(false),
_NeedToCleanUpTexture(false),
_ChangeScene(nullptr)
{	
	LOG("Director is Created\n");
}


Director::~Director()
{
	LOG("Director is Destroyed\n");
	for (int size = _SceneStack.size(); size > 0; size = _SceneStack.size())
	{
		_SceneStack.top()->Exit();
		_SceneStack.top()->Release();
		_SceneStack.pop();
	}
}

Director* Director::GetInstance()
{
	if (!_Instance)
		_Instance = new Director;

	return _Instance;
}

void Director::DestroyInstance()
{
	if (_Instance)
		delete _Instance;

	_Instance = nullptr;
}

void Director::RunWithScene(Scene* const scene)
{
	if (_SceneStack.size() == 0)
	{
		PushScene(scene);
	}
	else
		ASSERT(false, "이미 추가된 씬이 있습니다. Director::RunWithScene을 호출할수 없습니다.");
}

void Director::PushScene(Scene* const scene)
{
	_CameraPos = Point(WINDOW_X / 2, WINDOW_Y / 2);
	scene->Retain();
	scene->Init();
	_SceneStack.push(scene);
}

void Director::PopScene()
{
	_CameraPos = Point(WINDOW_X / 2, WINDOW_Y / 2);

	auto top = _SceneStack.top();
	top->Exit();
	top->Release();
	_SceneStack.pop();

	ASSERT(_SceneStack.size() != 0, "씬 스택이 비었습니다. 화면에 씬을 그릴 수 없습니다.");
}

void Director::NowReplaceScene()
{
	//cleanup texture pool
	if (_NeedToCleanUpTexture)
	{
		TextureManager::GetInstance()->DeleteAllTexture();
	}

	//pop
	auto top = _SceneStack.top();
	top->Exit();
	top->Release();
	_SceneStack.pop();

	//push
	ASSERT(_ChangeScene, "_ChangeScene is null!");
	PushScene(_ChangeScene);

	_NeedToCleanUpTexture = false;
	_ChangeScene = nullptr;
}

void Director::ReplaceScene(Scene* const scene, bool cleanUpTexturePool)
{
	_NeedToReplaceScene = true;
	_NeedToCleanUpTexture = cleanUpTexturePool;
	_ChangeScene = scene;
}

void Director::UpdateCurScene()
{
	_SceneStack.top()->Update();
	if (_NeedToReplaceScene)
	{
		_NeedToReplaceScene = false;

		NowReplaceScene();
	}
}

void Director::DrawCurScene() const
{
	HRESULT hr;
	if (SUCCEEDED(_d3dxSprite->Begin(D3DXSPRITE_ALPHABLEND)))
	{
		_SceneStack.top()->Draw(_d3dxSprite);
		V(_d3dxSprite->End())
	}

}

void Director::SetCameraPos(Point const &pos)
{
	_CameraPos = pos;
}

void Director::SetCameraPos(float x, float y)
{
	_CameraPos.x = x;
	_CameraPos.y = y;
}

void Director::SetCameraPosX(float x)
{
	_CameraPos.x = x;
}

void Director::SetCameraPosY(float y)
{
	_CameraPos.y;
}

Point Director::GetCameraPos() const
{
	return _CameraPos;
}

float Director::GetCameraPosX() const
{
	return _CameraPos.x;
}

float Director::GetCameraPosY() const
{
	return _CameraPos.y;
}

Rect Director::GetCameraBox() const
{
	float halfWidth = WINDOW_X / 2;
	float halfHeight = WINDOW_Y / 2;

	return Rect(_CameraPos.x - halfWidth, _CameraPos.y - halfHeight, WINDOW_X, WINDOW_Y);
}

void Director::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
	bool* pbNoFurtherProcessing, void* pUserContext)
{
	//if (_SceneStack.top())
	_SceneStack.top()->OnMsgProc(hWnd, uMsg, wParam, lParam,
								pbNoFurtherProcessing, pUserContext);
}

void Director::CreateD3DXSprite()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &_d3dxSprite);
}

void Director::ReleaseD3DXSprite()
{
	_d3dxSprite->Release();
}

LPD3DXSPRITE Director::GetD3DXSprite() const
{
	return _d3dxSprite;
}