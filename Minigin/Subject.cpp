#include "MiniginPCH.h"
#include "Subject.h"

#include "Observer.h"

void boop::Subject::AddObserver(Observer* pObserver)
{
	const auto itr = std::find(m_pObservers.begin(), m_pObservers.end(), pObserver);
	if (itr == m_pObservers.end())
	{
		m_pObservers.push_back(pObserver);
		pObserver->OnAdd();
	}
}

void boop::Subject::RemoveObserver(Observer* pObserver)
{
	const auto itr = std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver);
	pObserver->OnRemove();
}

void boop::Subject::Notify(const std::string& message)
{
	for (Observer* pObserver : m_pObservers)
	{
		if (pObserver != nullptr) //Todo: this should get deleted if == null
		{
			pObserver->OnNotify(message);	
		}
	}
}
