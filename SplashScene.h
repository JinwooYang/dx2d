#pragma once
#include "dx2dx.h"

class SplashScene
	: public dx2dx::Scene
{
private:
	DISALLOW_COPY_AND_ASSIGN(SplashScene);
	SplashScene();
	~SplashScene();

	dx2dx::Sprite* _Splash;

public:
	CREATE_FUNC(SplashScene);

	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
	virtual void OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
							bool *pbNoFurtherProcessing, void *pUserContext) override;
};

