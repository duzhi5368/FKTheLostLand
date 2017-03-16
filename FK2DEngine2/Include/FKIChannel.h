/**
*	created:		2013-4-23   21:14
*	filename: 		FKIChannel
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKIBase.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace audio
	{
		class IChannel : public FK2DEngine2::core::IBase
		{
		public:
			typedef unsigned long HCHANNEL;
			virtual const std::wstring getTypeInfo() const {
				return L"IChannel";
			}

			//! 释放本Channel
			void release(){
				// Channel已被Audio库管理，所以可以直接Delete
				delete this;
			}

			//! \return Channel的音量
			virtual float getVolume() = 0;

			//! \return Channel的平移位置 -1.0f - 1.0f 【-1.0f: 左声道, 0.0f 中心, 1.0f 右声道】
			virtual float getPan() = 0;

			//! 获取循环次数
			virtual int getLoopCount() = 0;

			//! 设置音量 0.0f -1.0f
			virtual void setVolume(float volume) = 0;

			//! 设置平移位置 -1.0f - 1.0f 【-1.0f: 左声道, 0.0f 中心, 1.0f 右声道】
			virtual void setPan(float pan) = 0;

			//! 设置循环次数
			virtual void setLoopCount(int loopCount) = 0;

			//! \return 正在播放则会返回true
			virtual bool isPlaying() = 0;

			//! 暂停
			virtual void setPaused(bool pause) = 0;

			//! 停止
			virtual void stop() = 0;

			//! 本Channel是否有效
			virtual bool isValid() = 0;

			//! 获取Handle句柄
			virtual HCHANNEL getHandle() = 0;
		};
	}
}
//------------------------------------------------------------------------