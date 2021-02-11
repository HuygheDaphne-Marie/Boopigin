#pragma once
#include "Singleton.h"
#include <chrono>


#define TIME_INSTANCE (&Time::GetInstance());
typedef std::chrono::high_resolution_clock::time_point TimePoint;

namespace boop
{
	class Time final : public boop::Singleton<Time>
	{
	public:
		void Start();
		void Update();
		float GetElapsedMilli() const;
		float GetMilliPerFrame() const;
		
		int m_DesiredFramePerSecond;

	private:
		Time();
		friend class boop::Singleton<Time>;
		
		TimePoint m_PreviousTime;
		double m_TimeSinceLastFrame;
	};
}

