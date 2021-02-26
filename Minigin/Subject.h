#pragma once
#include "Event.h"

namespace boop
{
	class Observer;

	class Subject
	{
	public:
		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);

		void Notify(const Event& event);

	private:
		std::vector<Observer*> m_pObservers{};
	};
}

