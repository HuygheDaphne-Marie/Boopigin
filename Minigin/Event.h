#pragma once
//Todo: Might make this a class later, if events would become more complex or maybe use a backboard type system
//class Event
//{
//};

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

//class IEventData
//{
//public:
//	IEventData() = default;
//	virtual ~IEventData() = default;
//};
//
//EventData does not take ownership of pointers whatsoever!
//template<typename T>
//class EventData : public IEventData
//{
//public:
//	explicit EventData(T data)
//		: m_Data(data)
//	{
//	}
//
//	T GetData()
//	{
//		return m_Data;
//	}
//	void SetData(T data)
//	{
//		m_Data = data;
//	}
//
//private:
//	T m_Data;
//};
//
//class Event final
//{
//public:
//	explicit Event(const std::string& message)
//		: Event(message, 0)
//	{
//	}
//	template<typename DataType>
//	explicit Event(const std::string& message, DataType data)
//		: m_Message(message)
//		, m_pEventData(new EventData<DataType>(data))
//	{
//	}
//	~Event()
//	{
//		delete m_pEventData;
//	}
//
//	const std::string m_Message;
//	IEventData* m_pEventData;
//};
