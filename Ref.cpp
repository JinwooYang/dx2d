#include "DXUT.h"
#include "Ref.h"
#include "AutoReleasePool.h"
#include "UserDefines.h"

USING_NS_DX2DX;

void PrintDelLog(const Ref* const obj)
{
#if (PRINT_OBJ_ADD_DEL_LOG)
	LOG("Del Obj! [%p]\n", obj);
#endif
}

void PrintAddLog(const Ref* const obj)
{
#if (PRINT_OBJ_ADD_DEL_LOG)
	LOG("Add Obj! [%p]\n", obj);
#endif
}

Ref::Ref() :
_nRefCount(1)
{
	PrintAddLog(this);
}


Ref::~Ref()
{
	PrintDelLog(this);
}

int Ref::Retain()
{
	++_nRefCount;
	return _nRefCount;
}

void Ref::Release()
{
	--_nRefCount;

	if (_nRefCount == 0)
	{
		delete this;
	}

	//return _nRefCount;
}

void Ref::AutoRelease()
{
	AutoReleasePool::GetInstance()->AddObject(this);
}

unsigned int Ref::GetRefCount() const
{
	return _nRefCount;
}