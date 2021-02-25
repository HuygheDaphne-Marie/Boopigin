#pragma once
#include <string>

class Event;

namespace boop
{
	// template <typename SubjectType, typename EventType = std::string> //todo: could event be a type and then just send events of a certain type with data already in them? 
	class Observer
	{
	public:
		//explicit Observer(SubjectType* pSubject);
		virtual ~Observer() = default;

		virtual void OnNotify(const std::string& message) = 0;
		
		virtual void OnAdd() = 0;
		virtual void OnRemove() = 0;

		//virtual void AddCallback(const std::string& event/*, function pointer to owner of the observer*/);

	//private:
		//SubjectType* m_pSubject;
	};


}



