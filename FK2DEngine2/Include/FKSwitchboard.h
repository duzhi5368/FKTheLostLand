/**
*	created:		2013-4-29   21:46
*	filename: 		FKSwitchboard
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <queue>
#include <set>
#include <map>
#include "FKMathUtil.h"
#include "FKMessage.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace event
	{
		class CSwitchboard
		{
		public:
			static CSwitchboard& GetInstance();
			
			void Broadcast(CMessage* message);
			void DeferredBroadcast(CMessage* message, float delay);
			
			void Update(float dt);

			const bool SubscribeTo(CMessageListener* subscriber, std::wstring messageType);
			const bool UnsubscribeFrom(CMessageListener* subscriber, std::wstring messageType);
			const std::set<CMessageListener*> GetSubscribersTo(std::wstring messageName);
			const std::set<std::wstring> GetSubscriptionsFor(CMessageListener* subscriber);

			void SendAllMessages();
			
		protected:
			CSwitchboard();
			static CSwitchboard* s_Switchboard;
			
		private:
			std::queue<CMessage*> _messages;
			
			std::map< std::wstring, std::set<CMessageListener*> > _subscribers;
			std::map< CMessageListener*, std::set<std::wstring> > _subscriptions;
			
			struct MessageTimer
			{
				CMessage* _message;
				float _timeRemaining;
				
				MessageTimer(CMessage* message, float timeRemaining)
				{
					_message = message;
					_timeRemaining = FK2DEngine2::math::CMathUtil::Max(0.0f, timeRemaining);
				}
			};
			std::vector<MessageTimer> _delayedMessages;
			
			struct SubscriptionInfo 
			{
				CMessageListener* _subscriber;
				std::wstring _messageType;
				
				SubscriptionInfo(CMessageListener* subscriber, std::wstring messageType) :
				_subscriber(subscriber),
				_messageType(messageType)
				{}
			};
			bool _messagesLocked;
			std::vector<SubscriptionInfo> _deferredAdds;
			std::vector<SubscriptionInfo> _deferredRemoves;
		};


		#define theSwitchboard FK2DEngine2::event::CSwitchboard::GetInstance()
	}
}