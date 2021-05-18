#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

#include "Event.h"

namespace boop
{
	class Observer final
	{
	public:		
		template <typename OwnerType>
		void AddEventCallback(const std::string& message, OwnerType* pOwner, void(OwnerType::* pFunction)(const Event&))
		{
			m_Callbacks[message].push_back(std::bind(pFunction, pOwner, std::placeholders::_1));
		}
		void OnNotify(const Event& event);

	private:
		std::unordered_map<std::string, std::vector<std::function<void(const Event&)>>> m_Callbacks{};
	};


}
