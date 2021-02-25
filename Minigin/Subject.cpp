#include "MiniginPCH.h"
#include "Subject.h"

#include "Observer.h"

void boop::Subject::AddObserver(std::weak_ptr<Observer> pObserver)
{
	const auto itr = std::find(m_pObservers.begin(), m_pObservers.end(), pObserver);
	if (itr == m_pObservers.end())
	{
		m_pObservers.push_back(pObserver);
		pObserver.lock()->OnAdd();
	}
}

void boop::Subject::RemoveObserver(std::weak_ptr<Observer> pObserver)
{
	const auto itr = std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver);
	pObserver.lock()->OnRemove();
}

void boop::Subject::Notify(const std::string& message)
{
	for (std::weak_ptr<Observer> pObserver : m_pObservers)
	{
		if (pObserver.use_count() != 0) //Todo: this should get deleted if == 0
		{
			pObserver.lock()->OnNotify(message);	
		}
	}
}
