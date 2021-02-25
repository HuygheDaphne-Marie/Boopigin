#pragma once
#include <memory>

namespace boop
{
	class Observer;

	class Subject
	{
	public:
		void AddObserver(std::weak_ptr<Observer> pObserver);
		void RemoveObserver(std::weak_ptr<Observer> pObserver);

		void Notify(const std::string& message);

	private:
		std::vector<std::weak_ptr<Observer>> m_pObservers{};
	};
}

