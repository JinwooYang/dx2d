#include "DXUT.h"
#include "AppDelegate.h"
#include "TitleScene.h"
#include "SplashScene.h"

USING_NS_DX2DX;

AppDelegate::AppDelegate()
{
}


AppDelegate::~AppDelegate()
{
}

void AppDelegate::AppLaunching()
{
	Director::GetInstance()->RunWithScene(SplashScene::Create());
}