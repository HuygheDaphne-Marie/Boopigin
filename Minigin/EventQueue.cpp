#include "MiniginPCH.h"
#include "EventQueue.h"
#include "IEventListener.h"

void EventQueue::Broadcast(Event* event)
{
	const QueuedEvent eventToBroadcast{QueuedEventType::broadcast, event};
	GetQueuedEventsActiveScene().push(eventToBroadcast);
}
void EventQueue::Transmit(Event* event)
{
	const QueuedEvent eventToBroadcast{ QueuedEventType::transmit, event };
	GetQueuedEventsActiveScene().push(eventToBroadcast);
}

void EventQueue::Subscribe(const std::string& eventType, IEventListener* listener)
{
	auto& listeners = GetListenersActiveScene();
	
	if (listeners.find(eventType) != listeners.end())
	{
		const auto& itr = std::find(
			listeners[eventType].begin(), 
			listeners[eventType].end(), 
			listener);

		if (itr == listeners[eventType].end())
		{
			listeners[eventType].push_back(listener);
		}
	}
	else
	{
		listeners[eventType] = std::vector<IEventListener*>{ listener };
	}
}
void EventQueue::Unsubscribe(IEventListener* listener)
{
	auto& listeners = GetListenersActiveScene();
	
	for (auto& pair : listeners)
	{
		Unsubscribe(pair.first, listener);
	}
}
void EventQueue::Unsubscribe(const std::string& eventType, IEventListener* listener)
{
	auto& listeners = GetListenersActiveScene();
	
	if (listeners.find(eventType) != listeners.end())
	{
		const auto listenerItr = std::find(
			listeners[eventType].begin(), 
			listeners[eventType].end(), 
			listener);
		
		if (listenerItr != listeners[eventType].end())
		{
			listeners[eventType].erase(listenerItr);
		}
	}
}

void EventQueue::HandleQueue()
{
	auto& queuedEvents = GetQueuedEventsActiveScene();
	auto& listeners = GetListenersActiveScene();
	
	while (!queuedEvents.empty())
	{
		auto& e = queuedEvents.front();
		if (e.type == QueuedEventType::broadcast)
		{
			for (auto& listener : listeners[e.event->message])
			{
				listener->OnEvent(*e.event);
			}
		}
		else
		{
			for (auto& listener : listeners[e.event->message])
			{
				if (listener->OnEvent(*e.event))
					break;
			}
		}
		delete e.event;
		queuedEvents.pop();
	}
}

std::map<std::string, std::vector<IEventListener*>>& EventQueue::GetListenersActiveScene()
{
	const auto activeScene = boop::SceneManager::GetInstance().GetActiveScene();
	return GetListenersForScene(activeScene);
}
std::map<std::string, std::vector<IEventListener*>>& EventQueue::GetListenersForScene(std::shared_ptr<boop::Scene> scene)
{
	const auto findItr = m_ListenersByScene.find(scene);
	if (findItr == m_ListenersByScene.end())
	{
		m_ListenersByScene[scene] = std::map<std::string, std::vector<IEventListener*>>{};
	}

	return m_ListenersByScene[scene];
}

std::queue<QueuedEvent>& EventQueue::GetQueuedEventsActiveScene()
{
	const auto activeScene = boop::SceneManager::GetInstance().GetActiveScene();
	return GetQueuedEventsForScene(activeScene);
}
std::queue<QueuedEvent>& EventQueue::GetQueuedEventsForScene(std::shared_ptr<boop::Scene> scene)
{
	const auto findItr = m_QueuedEventsByScene.find(scene);
	if (findItr == m_QueuedEventsByScene.end())
	{
		m_QueuedEventsByScene[scene] = std::queue<QueuedEvent>{};
	}

	return m_QueuedEventsByScene[scene];
}
