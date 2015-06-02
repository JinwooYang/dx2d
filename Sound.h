//#pragma once
//#include <fmod.h>
//#include <vector>
//#include "dx2dxMacros.h"
//
//struct SoundInfo
//{
//	FMOD_SOUND **_ppSound;
//	int _Num;
//
//	SoundInfo(FMOD_SOUND **ppSound, int num)
//	{
//		_ppSound = ppSound;
//		_Num = num;
//	}
//};
//
//NS_DX2DX
//{
//	class Sound
//	{
//	private:
//		DISALLOW_COPY_AND_ASSIGN(Sound);
//		static std::vector<SoundInfo> SOUND_POOL;
//		static FMOD_SYSTEM *_pSystem;
//		Sound();
//
//	public:
//		~Sound();
//
//		static void CreateSound(char* fileName, FMOD_MODE mode, int indexNum);
//		static void Update()
//		{
//			FMOD_System_Update(_pSystem);
//		}
//		static void Play(int indexNum, FMOD_CHANNEL **channel, FMOD_CHANNELINDEX channel_id = FMOD_CHANNEL_FREE);
//		static void Stop(FMOD_CHANNEL* channel);
//		static void CleanUpSound(int indexNum); //* CleanUpSound는 만들고 테스트한적이 없는 함수임
//		static void CleanUpAllSounds();
//	};
//}
//
