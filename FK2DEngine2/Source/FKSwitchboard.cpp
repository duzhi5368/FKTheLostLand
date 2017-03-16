/**
*	created:		2013-4-29   21:52
*	filename: 		FKSwitchboard
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKSwitchboard.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace event
	{
		//------------------------------------------------------------------------
		CSwitchboard* CSwitchboard::s_Switchboard = NULL;
		//------------------------------------------------------------------------
		CSwitchboard::CSwitchboard()
		{
			_messagesLocked = false;
		}
		//------------------------------------------------------------------------
		CSwitchboard& CSwitchboard::GetInstance()
		{
			if (s_Switchboard == NULL)
			{
				s_Switchboard = new CSwitchboard();
			}
			return *s_Switchboard;
		}
		//------------------------------------------------------------------------
		void CSwitchboard::Broadcast(CMessage* message)
		{
			_messages.push(message);
		}
		//------------------------------------------------------------------------
		void CSwitchboard::DeferredBroadcast(CMessage* message, float delay)
		{
			MessageTimer mt(message, delay);
			_delayedMessages.push_back(mt);
		}
		//------------------------------------------------------------------------
		void CSwitchboard::Update(float dt)
		{
			std::vector<MessageTimer>::iterator it = _delayedMessages.begin();
			while (it != _delayedMessages.end())
			{
				(*it)._timeRemaining -= dt;
				if ((*it)._timeRemaining <= 0.0f)
				{
					Broadcast((*it)._message);
					it = _delayedMessages.erase(it);
				}
				else
				{
					it++;
				}
			}
		}
		//------------------------------------------------------------------------
		const bool CSwitchboard::SubscribeTo(CMessageListener* subscriber, std::wstring messageType)
		{
			if (_messagesLocked)
			{
				_deferredAdds.push_back(SubscriptionInfo(subscriber, messageType));
				return false;
			}

			_subscriptions[subscriber].insert(messageType);
			std::pair<std::set<CMessageListener*>::iterator, bool> insertResult = _subscribers[messageType].insert(subscriber);
			return insertResult.second;
		}
		//------------------------------------------------------------------------
		const bool CSwitchboard::UnsubscribeFrom(CMessageListener* subscriber, std::wstring messageType)
		{
			if (_messagesLocked)
			{
				_deferredRemoves.push_back(SubscriptionInfo(subscriber, messageType));
				return false;
			}

			if (_subscribers.find(messageType) == _subscribers.end())
			{
				return false;
			}
			std::set<CMessageListener*>::iterator it = _subscribers[messageType].find(subscriber);
			if (it == _subscribers[messageType].end())
			{
				return false;
			}
			else
			{
				_subscribers[messageType].erase(it);
				std::set< std::wstring >::iterator sIt = _subscriptions[subscriber].find(messageType);
				if (sIt != _subscriptions[subscriber].end())
					_subscriptions[subscriber].erase(sIt);
				return true;
			}
		}
		//------------------------------------------------------------------------
		const std::set<CMessageListener*> CSwitchboard::GetSubscribersTo(std::wstring messageType)
		{
			if (_subscribers.find(messageType) == _subscribers.end())
			{
				return std::set<CMessageListener*>();
			}
			else
			{
				return _subscribers[messageType];		
			}
		}
		//------------------------------------------------------------------------
		const std::set< std::wstring > CSwitchboard::GetSubscriptionsFor(CMessageListener* subscriber)
		{
			if (_subscriptions.find(subscriber) == _subscriptions.end())
			{
				return std::set< std::wstring >();
			}
			else
			{
				return _subscriptions[subscriber];
			}
		}
		//------------------------------------------------------------------------
		void CSwitchboard::SendAllMessages()
		{
			_messagesLocked = true;
			while (!_messages.empty())
			{
				if (_subscribers.find(_messages.front()->GetMessageName()) != _subscribers.end())
				{
					std::set<CMessageListener*>::iterator listenIt = _subscribers[_messages.front()->GetMessageName()].begin();
					while (listenIt != _subscribers[_messages.front()->GetMessageName()].end())
					{
						(*listenIt)->ReceiveMessage(_messages.front());
						listenIt++;
					}
				}
				delete _messages.front();
				_messages.pop();
			}
			_messagesLocked = false;

			for(unsigned int i = 0; i < _deferredRemoves.size(); i++)
			{
				UnsubscribeFrom(_deferredRemoves[i]._subscriber, _deferredRemoves[i]._messageType);
			}
			_deferredRemoves.clear();

			for(unsigned int i = 0; i < _deferredAdds.size(); i++)
			{
				SubscribeTo(_deferredAdds[i]._subscriber, _deferredAdds[i]._messageType);
			}
			_deferredAdds.clear();
		}
		//------------------------------------------------------------------------
	}
}
