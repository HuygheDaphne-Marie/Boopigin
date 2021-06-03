#pragma once
#include "Singleton.h"
#include <queue>
#include <map>
#include "Event.h"
#include "IEventListener.h"

enum class QueuedEventType
{
	broadcast,
	transmit
};

struct QueuedEvent
{
	QueuedEventType type;
	Event* event;
};

class EventQueue final : public boop::Singleton<EventQueue>
{
public:
	void Broadcast(Event* event); // is sent to all listeners
	void Transmit(Event* event); // is sent to single listener

	void Subscribe(const std::string& eventType, IEventListener* listener);
	void Unsubscribe(IEventListener* listener);
	void Unsubscribe(const std::string& eventType, IEventListener* listener);
	
	void HandleQueue();

private:
	friend class Singleton<EventQueue>;
	EventQueue() = default;
	
	std::queue<QueuedEvent> m_QueuedEvents;
	std::map<std::string, std::vector<IEventListener*>> m_Listeners;
};

