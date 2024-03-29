#pragma once
#include "Singleton.h"
#include <queue>
#include <map>
#include "Event.h"
#include "SceneManager.h"
//#include "IEventListener.h"
class IEventListener;

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

	std::map<std::weak_ptr<boop::Scene>, std::queue<QueuedEvent>, std::owner_less<std::weak_ptr<boop::Scene>>> m_QueuedEventsByScene;
	std::map<std::weak_ptr<boop::Scene>, std::map<std::string, std::vector<IEventListener*>>, std::owner_less<std::weak_ptr<boop::Scene>>> m_ListenersByScene;

	std::map<std::string, std::vector<IEventListener*>>& GetListenersActiveScene();
	std::map<std::string, std::vector<IEventListener*>>& GetListenersForScene(std::shared_ptr<boop::Scene> scene);

	std::queue<QueuedEvent>& GetQueuedEventsActiveScene();
	std::queue<QueuedEvent>& GetQueuedEventsForScene(std::shared_ptr<boop::Scene> scene);
};

