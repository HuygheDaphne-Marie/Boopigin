#pragma once
#include "Event.h"

class IEventListener
{
public:
	virtual ~IEventListener() = default;
	virtual bool OnEvent(const Event& event) = 0;
};
