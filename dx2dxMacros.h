#pragma once
#include <Windows.h>

#define DISALLOW_COPY_AND_ASSIGN(type)		\
	type(const type&) = delete;				\
	void operator=(const type&) = delete;





#if defined(DEBUG) || defined(_DEBUG)
	#define ASSERT(cond, message)				\
		if(!(cond))								\
		{										\
			OutputDebugStringA(message "\n");	\
			LOG(message "\n");				\
			assert(cond);						\
		}
#else
	#define ASSERT(cond, message)
#endif

// * �ݵ�� private�������� �����Ͻʽÿ�.
// * ��ũ�� ���ο� ����Ʈ �����ڿ� �ı��ڰ� ���ǵǾ� �ֽ��ϴ�.
#define SINGLETONE(type)				\
	type();								\
	~type();							\
	static type* _Instance;				\
										\
public:									\
	static type* GetInstance()			\
	{									\
		if(!_Instance)					\
			_Instance = new type;		\
		return _Instance;				\
	}									\
										\
	static void DestroyInstance()		\
	{									\
		if(_Instance)					\
			delete _Instance;			\
		_Instance = nullptr;			\
	}									\
private:								\



#define SINGLETONE_INSTANCE_INIT(type, val)\
type* type::_Instance = val




#define NS_DX2DX namespace dx2dx
#define USING_NS_DX2DX using namespace dx2dx






#define CREATE_FUNC(type)			\
static type* Create()				\
{									\
	type* obj = new type;			\
	obj->AutoRelease();				\
	return obj;						\
}

#define CLONE_FUNC(type)		\
type* Clone()						\
{									\
	auto clone = type::Create();	\
	return clone;					\
}

#if defined(DEBUG) || defined(_DEBUG)
#define LOG printf
#else
#define LOG(format, ...)
#endif
