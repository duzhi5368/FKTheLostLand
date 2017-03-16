/**
*	created:		2013-4-23   21:45
*	filename: 		FKFmodAudioDriver
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKLogger.h"

#include "../Include/FKFmodChannel.h"
#include "../Include/FKFmodSound.h"
#include "../Include/FKFmodAudioDriver.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2::core;
//------------------------------------------------------------------------
#pragma comment (lib,"fmodex_vc.lib")
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace audio
	{
		CFmodAudioDriver::CFmodAudioDriver()
		{
			system = 0;
		}

		CFmodAudioDriver::~CFmodAudioDriver()
		{
		}

		bool CFmodAudioDriver::initDriver()
		{
			FMOD_RESULT result;
			result = FMOD::System_Create(&system);
			if (result != FMOD_OK)
			{
				LogError( L"Fmod音频驱动创建失败...");
				return false;
			}
			result = system->init(200,FMOD_INIT_NORMAL,0);
			if (result != FMOD_OK)
			{
				LogError( L"音频驱动初始化失败...");
				system->release();
				return false;
			}
			LogInfo( L"音频驱动初始化完成...");
			return true;
		}

		bool CFmodAudioDriver::updateDriver()
		{
			FMOD_RESULT result = system->update();
			if (result != FMOD_OK)
				return false;
			return true;
		}

		bool CFmodAudioDriver::shutDriver()
		{
			FMOD_RESULT result = system->release();
			if (result != FMOD_OK)
			{
				LogError( L"Fmod音频驱动关闭失败..." );
				system = NULL;
				return false;
			}
			else 
			{
				LogInfo( L"Fmod音频驱动关闭完成..." );
				system = NULL;
				return true;
			}
		}
			
		IChannel * CFmodAudioDriver::playSound(ISound * isound,float volume,float pan ,int loopCount,bool getChannel)
		{
			FMOD::Channel * channel = NULL;
			if( isound == NULL )
			{
				LogError( L"声音文件不存在" );
				return NULL;
			}
			FMOD::Sound * sound = (FMOD::Sound *)isound->getHandle();
			FMOD_RESULT result = system ->playSound(FMOD_CHANNEL_FREE,sound,true,&channel);
			if (result != FMOD_OK)
				return NULL;
			channel->setVolume(volume);
			channel->setPan(pan);
			channel->setLoopCount(loopCount);
			channel->setPaused(false);
			if (getChannel == true)
			{
				IChannel * retc = new CFmodChannel(channel);
				return retc;
			}
			return NULL;
		}

		ISound * CFmodAudioDriver::loadSound(const std::wstring & soundName,const std::wstring & fileName,E_SOUND_TYPE type)
		{
			CFmodSound * sound = new CFmodSound(soundName);
			bool result = false;
			switch (type)
			{
			case E_SOUND_TYPE_SAMPLE :
				result = sound->loadSample(fileName,system); 
				break;
			case E_SOUND_TYPE_STREAM :
				result = sound->loadStream(fileName,system);
				break;
			}
			if (result == false)
			{
				LogError( L"声音文件加载失败 : %s", fileName.c_str() );
				return NULL;
			}
			if (resourceMap ->addResource(sound) == false)
			{
				sound->decRef();
				LogWarn( L"声音文件插入资源表失败...(有可能已存在于资源表)  : %s", fileName.c_str() );
				return NULL;
			}
			LogInfo(  L"声音文件加载成功 : %s", fileName.c_str() );
			return sound;
		}

		bool CFmodAudioDriver::freeSound(const std::wstring & soundName)
		{
			IResource * sound = resourceMap->getResourceByName(soundName);
			if (sound == NULL)
			{
				LogError( L"释放音频文件失败，无法从资源表中查找 : %s", soundName.c_str() );
				return false;
			}
			if (sound->getTypeInfo() != L"CFmodSound")
			{
				LogWarn( L"尝试释放一个非FMod的音频资源 : %s", sound->getTypeInfo() );
				return false;
			}
			resourceMap->freeResource(sound);
			return true;
		}

		bool CFmodAudioDriver::freeSound(ISound * sound)
		{
			if (sound == NULL)
			{
				LogError( L"无法释放一个音频资源空指针" );
				return false;
			}
			if (sound->getTypeInfo() != L"CFmodSound")
			{
				LogWarn( L"尝试释放一个非FMod的音频资源 : %s", sound->getTypeInfo() );
				return false;
			}
			resourceMap->freeResource(sound);
			return true;
		}
	}
}
//------------------------------------------------------------------------