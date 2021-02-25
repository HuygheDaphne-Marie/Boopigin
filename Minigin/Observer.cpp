#include "MiniginPCH.h"
#include "Observer.h"

void boop::Observer::OnNotify(const std::string& message)
{
	for (auto callback : m_Callbacks[message])
	{
		callback();
	}
}
