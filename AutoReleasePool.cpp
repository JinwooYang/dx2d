#include "DXUT.h"
#include "AutoReleasePool.h"
#include "UserDefines.h"

USING_NS_DX2DX;

AutoReleasePool* AutoReleasePool::_Instance = nullptr;


AutoReleasePool::AutoReleasePool()
{
	_AutoReleasePool.reserve(200);
	LOG("AutoReleasePool is Created\n");
}


AutoReleasePool::~AutoReleasePool()
{
	//Clear();

	for (auto& pObj : _AutoReleasePool)
	{
		delete pObj;
		//PrintDelLog(pObj);
	}
	LOG("Delete All Object!\n");

	LOG("AutoReleasePool is Destroyed\n");
}


AutoReleasePool* AutoReleasePool::GetInstance()
{
	if (!_Instance)
		_Instance = new AutoReleasePool;

	return _Instance;
}

void AutoReleasePool::DestroyInstance()
{
	if (_Instance)
		delete _Instance;

	_Instance = nullptr;
}

void AutoReleasePool::AddObject(Ref* pObj)
{
	auto result = std::find(_AutoReleasePool.begin(), _AutoReleasePool.end(), pObj);
	if (_AutoReleasePool.end() != result)
	{
		ASSERT(false, "이미 오토릴리즈풀에 추가된 객체!");
		return;
	}
	_AutoReleasePool.push_back(pObj);
}


void AutoReleasePool::Clear()
{
	if (_AutoReleasePool.size() == 0) return;

	for (auto obj : _AutoReleasePool)
	{
		obj->Release();
	}
	_AutoReleasePool.clear();
}