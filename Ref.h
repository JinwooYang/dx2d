#pragma once
#include <list>
#include "dx2dxMacros.h"

NS_DX2DX
{
	class Ref
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(Ref);
		unsigned int _nRefCount;

	protected:
		Ref();
	public:
		virtual ~Ref();

	public:
		virtual int Retain() final;
		virtual void Release() final;
		void AutoRelease();
		unsigned int GetRefCount() const;
	};
}