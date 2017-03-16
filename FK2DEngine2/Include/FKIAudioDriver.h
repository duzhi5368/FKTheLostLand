/**
*	created:		2013-4-23   21:19
*	filename: 		FKIAudioDriver
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once

#include "FKIBase.h"
#include "FKResourceMap.h"

#include "FKIChannel.h"
#include "FKISound.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace audio
	{
		typedef enum
		{
			E_SOUND_TYPE_SAMPLE,
			E_SOUND_TYPE_STREAM
		}E_SOUND_TYPE;

		class IAudioDriver : public FK2DEngine2::core::IBase
		{
		public :
			virtual const std::wstring getTypeInfo() const {
				return L"IAudioDriver";
			}
			virtual ~IAudioDriver(){}
			IAudioDriver(){}

			//! 初始化音频设备
			virtual bool initDriver() = 0;

			//! 更新音频设备
			virtual bool updateDriver() = 0;

			//! 关闭音频设备
			virtual bool shutDriver() = 0;

			//! 播放声音
			//! \return 播放这个声音的Channel
			//! \params volume : 0.0f - 1.0f 声音的大小
			//! \params pan : -1.0f - 1.0f -1.0f: 左声道, 0.0f 中心, 1.0f 右声道
			//! \params loopCount : 循环播放次数。【-1 永远，0 一次】
			//! \params getChannel : 是否要求获取该Channel的句柄【如果你手动获取了该句柄，则当它无效时你需要手动调用 release() 函数释放它】
			virtual IChannel * playSound(ISound * sound,float volume = 1.0f,float pan = 0.0f,int loopCount = 0,bool getChannel = false) = 0;

			//! 加载音效
			//! \params type: E_SOUND_TYPE_SAMPLE 作为一个文件加载声音
			//! \params type: E_SOUND_TYPE_STREAM 作为一个流文件加载声音
			virtual ISound * loadSound(const std::wstring & soundName,const std::wstring & fileName,E_SOUND_TYPE type) = 0;

			//! 释放声音
			//! \return 如果找到了该声音并且释放掉，则返回true
			virtual bool freeSound(const std::wstring & soundName) = 0;

			//! 释放声音
			//! \return 如果找到了该声音并且释放掉，则返回true
			virtual bool freeSound(ISound * sound) = 0;

		public:
			FK2DEngine2::core::CResourceMap * getResourceMap(){
				return resourceMap;
			}
			FK2DEngine2::core::CResourceMap * setResourceMap(FK2DEngine2::core::CResourceMap * resourceMap_){
				FK2DEngine2::core::CResourceMap * ret = resourceMap;
				resourceMap = resourceMap_;
				return ret;
			}
		protected: 
			FK2DEngine2::core::CResourceMap * resourceMap;
		};
	}
}
//------------------------------------------------------------------------