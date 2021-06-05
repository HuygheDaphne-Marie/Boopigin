#pragma once
#include "Event.h"
#include "EventQueue.h"

class IEventListener
{
public:
	virtual ~IEventListener();
	virtual bool OnEvent(const Event& event) = 0;
};

inline IEventListener::~IEventListener()
{
	EventQueue::GetInstance().Unsubscribe(this);
}
