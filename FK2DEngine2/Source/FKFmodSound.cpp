/**
*	created:		2013-4-23   21:40
*	filename: 		FKFmodSound
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKLogger.h"
#include "../Include/FKFmodSound.h"
#include "../Include/FKStringConvert.h"
//------------------------------------------------------------------------
#pragma comment (lib,"fmodex_vc.lib")
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace audio
	{
		CFmodSound::CFmodSound(const std::wstring & soundName)
			:ISound(soundName){
			sound = NULL;
		}
		CFmodSound::~CFmodSound()
		{
			releaseSound();
		}

		ISound::HSOUND CFmodSound::getHandle()
		{
			return (ISound::HSOUND)(sound);
		}

		bool CFmodSound::loadSample(const std::wstring & fileName,FMOD::System * system)
		{
			char szFileName[MAX_PATH * 2];
			FK2DEngine2::core::WcharToChar( fileName.c_str(), szFileName, MAX_PATH * 2 );

			FMOD_RESULT result = system->createSound(szFileName,FMOD_2D | FMOD_LOOP_NORMAL |FMOD_SOFTWARE,0,&sound);
			if (result != FMOD_OK || sound == NULL)
			{
				LogError( L"加载音频文件失败 : %s", fileName );
				return false;
			}
			LogInfo( L"加载音频文件成功 : %s", fileName  );
			return true;
		}
		bool CFmodSound::loadStream(const std::wstring & fileName,FMOD::System * system)
		{
			char szFileName[MAX_PATH * 2];
			FK2DEngine2::core::WcharToChar( fileName.c_str(), szFileName, MAX_PATH * 2 );

			FMOD_RESULT result = system->createStream(szFileName,FMOD_2D | FMOD_LOOP_NORMAL |FMOD_HARDWARE,0,&sound);
			if (result != FMOD_OK || sound == NULL)
			{
				LogError( L"加载文件流失败 : %s", fileName.c_str() );
				return false;
			}
			LogInfo( L"加载文件流成功 : %s", fileName.c_str() );
			return true;
		}
		bool CFmodSound::releaseSound()
		{
			if (sound != NULL)
			{
				FMOD_RESULT result;
				result = sound->release();
				if (result != FMOD_OK)
				{
					LogError( L"音频文件释放失败 : %s", getObjectName().c_str() );
					sound = NULL;
					return false;
				}
				else 
				{
					LogInfo( L"音频文件释放成功 : %s",getObjectName().c_str() );
					sound = NULL;
					return true;
				}
				
			}
			return false;
		}
	}
}
//------------------------------------------------------------------------