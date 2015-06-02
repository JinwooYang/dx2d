#include "DXUT.h"
#include "Scene.h"
#include "TextureManager.h"

USING_NS_DX2DX;

Scene::Scene()
{
}


Scene::~Scene()
{
	//TextureManager::GetInstance()->DeleteAllTexture();
}

Scene* Scene::Create()
{
	auto scene = new Scene;
	scene->AutoRelease();
	scene->SetAnchorPoint(Point::ANCHOR_TOP_LEFT);

	return scene;
}

void Scene::Init()
{
	OnInit();
}

void Scene::Update()
{
	for (auto child : _ChildPool)
	{
		child->EarlyUpdate();
	}
	OnUpdate();
}

void Scene::Exit()
{
	OnExit();
	ActionManager::GetInstance()->DeleteAllAction();
}
