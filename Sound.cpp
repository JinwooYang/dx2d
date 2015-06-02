#include "DXUT.h"
//#include "Sound.h"
//
//USING_NS_DX2DX;
//
//FMOD_SYSTEM *Sound::_pSystem;
//std::vector<SoundInfo> Sound::SOUND_POOL;
//
//Sound::Sound()
//{
//	FMOD_System_Create(&_pSystem);
//	FMOD_System_Init(_pSystem, 32, FMOD_INIT_NORMAL, NULL);
//}
//
//
//Sound::~Sound()
//{
//	CleanUpAllSounds();
//	FMOD_System_Close(_pSystem);
//	FMOD_System_Release(_pSystem);
//}
//
//void Sound::CreateSound(char* fileName, FMOD_MODE mode, int indexNum)
//{
//	static Sound singletone;
//
//	FMOD_SOUND** sound = new FMOD_SOUND*();
//
//	for (unsigned int i = 0; i<SOUND_POOL.size(); i++)
//	{
//		if (SOUND_POOL[i]._Num == indexNum)
//		{
//			LOG("사운드 생성 실패 (이미 지정된 인덱스 값)");
//			return;
//		}
//	}
//	FMOD_System_CreateSound(_pSystem, fileName, mode, 0, sound);
//	//SoundInfo *soundInfo = new SoundInfo(sound, indexNum);
//	SOUND_POOL.push_back(SoundInfo(sound, indexNum));
//}
//
//void Sound::Play(int indexNum, FMOD_CHANNEL** channel, FMOD_CHANNELINDEX channel_id)
//{
//	int index;
//	for (unsigned int i = 0; i < SOUND_POOL.size(); i++)
//	{
//		if (SOUND_POOL[i]._Num == indexNum)
//		{
//			index = i;
//			FMOD_System_PlaySound(_pSystem, channel_id, *SOUND_POOL[index]._ppSound, false, channel);
//			return;
//		}
//	}
//	LOG("사운드 재생 실패 (찾을 수 없는 항목)");
//}
//
//void Sound::Stop(FMOD_CHANNEL* channel)
//{
//	FMOD_Channel_Stop(channel);
//}
//
//void Sound::CleanUpSound(int indexNum)
//{
//	for (unsigned int i = 0; i < SOUND_POOL.size(); i++)
//	{
//		if (SOUND_POOL[i]._Num == indexNum)
//		{
//			FMOD_Sound_Release(*SOUND_POOL[i]._ppSound);
//			delete SOUND_POOL[i]._ppSound;
//			SOUND_POOL.erase(SOUND_POOL.begin() + i);
//			return;
//		}
//	}
//}
//
//void Sound::CleanUpAllSounds()
//{
//	for (unsigned int i = 0; i < SOUND_POOL.size(); i++)
//	{
//		FMOD_Sound_Release(*SOUND_POOL[i]._ppSound);
//		delete SOUND_POOL[i]._ppSound;
//		//delete SOUND_POOL[i];
//	}
//	SOUND_POOL.erase(SOUND_POOL.begin(), SOUND_POOL.end());
//}