#pragma once
#include <string>

struct IEventData
{
};

template<typename DataType>
struct EventData : IEventData
{
	explicit EventData(DataType data)
		: data(data)
	{
	}	
	
	DataType data;
};


struct Event
{
	explicit Event(const std::string& message)
		: Event(message, nullptr)
	{
	}
	template<typename DataType>
	explicit Event(const std::string& message, DataType data)
		: message(message)
		, pEventData(new EventData<DataType>(data))
	{
	}
	Event(Event& other) = delete;
	Event(Event&& other) = delete;
	Event operator=(Event& other) = delete;
	Event operator=(Event&& other) = delete;
	
	~Event()
	{
		delete pEventData;
	}

	template<typename GetDataType>
	const GetDataType& GetData() const
	{
		return static_cast<EventData<GetDataType>*>(pEventData)->data;
	}
	
	const std::string message;
	IEventData* pEventData;
};
