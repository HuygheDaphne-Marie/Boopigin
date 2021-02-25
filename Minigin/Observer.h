#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

class Event;

namespace boop
{
	// template <typename SubjectType, typename EventType = std::string> //todo: could event be a type and then just send events of a certain type with data already in them? 
	class Observer final
	{
	public:
		template <typename OwnerType>
		void AddEventCallback(const std::string& message, OwnerType* pOwner, void(OwnerType::* pFunction)())
		{
			m_Callbacks[message].push_back(std::bind(pFunction, pOwner));
		}
		void OnNotify(const std::string& message);

	private:
		std::unordered_map<std::string, std::vector<std::function<void()>>> m_Callbacks{};
	};


}

//template <typename OwnerType>
//inline void boop::Observer::AddEventCallback(const std::string& message, OwnerType* pOwner, void(OwnerType::* pFunction)())
//{
//	m_Callbacks[message] = pFunction;
//}

