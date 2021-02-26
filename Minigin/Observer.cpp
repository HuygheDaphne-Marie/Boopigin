#include "MiniginPCH.h"
#include "Observer.h"

void boop::Observer::OnNotify(const Event& event)
{
	for (auto callback : m_Callbacks[event.message])
	{
		callback(event);
	}
}
