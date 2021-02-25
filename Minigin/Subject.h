#pragma once

namespace boop
{
	class Observer;

	class Subject
	{
	public:
		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);

		void Notify(const std::string& message);

	private:
		std::vector<Observer*> m_pObservers{};
	};
}

