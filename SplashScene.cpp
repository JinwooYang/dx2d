#include "DXUT.h"
#include "SplashScene.h"
#include "UserDefines.h"
#include "TitleScene.h"

USING_NS_DX2DX;


SplashScene::SplashScene()
{
}


SplashScene::~SplashScene()
{
}


void SplashScene::OnInit()
{

	_Splash = Sprite::Create(LR"(Resources/Images/splash.jpg)");
	_Splash->SetPosition(WINDOW_X / 2, WINDOW_Y / 2);
	_Splash->SetRotAngle(90);
	_Splash->SetColorA(0);
	this->AddChild(_Splash);

	auto spr = Sprite::Create(LR"(Resources/Images/splash.jpg)");
	spr->SetScale(0.2f);
	_Splash->AddChild(spr);


	_Splash->RunAction(Sequence::Create({
		TintTo::Create(5.0f, Color4F::WHITE),
		TintTo::Create(5.0f, Color4F::INVISIBLE),
		CallFunc::Create([]()
		{
			Director::GetInstance()->ReplaceScene(TitleScene::Create());
		})}));
}


void SplashScene::OnUpdate()
{
	_Splash->RotateBy(1);
}


void SplashScene::OnExit()
{

}


void SplashScene::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
							bool *pbNoFurtherProcessing, void *pUserContext)
{

}