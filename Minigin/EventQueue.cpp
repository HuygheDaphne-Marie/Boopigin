#include "MiniginPCH.h"
#include "EventQueue.h"

void EventQueue::Broadcast(Event* event)
{
	const QueuedEvent eventToBroadcast{QueuedEventType::broadcast, event};
	m_QueuedEvents.push(eventToBroadcast);
}
void EventQueue::Transmit(Event* event)
{
	const QueuedEvent eventToBroadcast{ QueuedEventType::transmit, event };
	m_QueuedEvents.push(eventToBroadcast);
}

void EventQueue::Subscribe(const std::string& eventType, IEventListener* listener)
{
	if (m_Listeners.find(eventType) != m_Listeners.end())
	{
		const auto& itr = std::find(
			m_Listeners[eventType].begin(), 
			m_Listeners[eventType].end(), 
			listener);

		if (itr == m_Listeners[eventType].end())
		{
			m_Listeners[eventType].push_back(listener);
		}
	}
	else
	{
		m_Listeners[eventType] = std::vector<IEventListener*>{ listener };
	}
}
void EventQueue::Unsubscribe(IEventListener* listener)
{
	for (auto& pair : m_Listeners)
	{
		Unsubscribe(pair.first, listener);
	}
}
void EventQueue::Unsubscribe(const std::string& eventType, IEventListener* listener)
{
	if (m_Listeners.find(eventType) != m_Listeners.end())
	{
		m_Listeners[eventType].erase(
		std::find(m_Listeners[eventType].begin(), m_Listeners[eventType].end(), listener)
		);
	}
}

void EventQueue::HandleQueue()
{
	while (!m_QueuedEvents.empty())
	{
		auto& e = m_QueuedEvents.front();
		if (e.type == QueuedEventType::broadcast)
		{
			for (auto& listener : m_Listeners[e.event->message])
			{
				listener->OnEvent(*e.event);
			}
		}
		else
		{
			for (auto& listener : m_Listeners[e.event->message])
			{
				if (listener->OnEvent(*e.event))
					break;
			}
		}
		delete e.event;
		m_QueuedEvents.pop();
	}
}
