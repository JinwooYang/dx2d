#pragma once
#include <vector>
#include "Ref.h"

NS_DX2DX
{
	class AutoReleasePool final
	{
		friend class Game;
	private:
		DISALLOW_COPY_AND_ASSIGN(AutoReleasePool);
		AutoReleasePool();
		~AutoReleasePool();

	public:
		static AutoReleasePool* GetInstance();
	private:
		static void DestroyInstance();

	private:
		static AutoReleasePool *_Instance;
		std::vector<Ref*> _AutoReleasePool;

	public:
		void AddObject(Ref* pObj);
		void Clear();
	};
}