#pragma once
#include "Singleton.h"
#include <chrono>


#define TIME_INSTANCE (&Timer::GetInstance());
typedef std::chrono::high_resolution_clock::time_point TimePoint;

namespace boop
{
	class Timer final : public boop::Singleton<Timer>
	{
	public:
		void Start();
		void Update();
		[[nodiscard]] int GetElapsedMilli() const;
		[[nodiscard]] float GetElapsedSec() const;
		[[nodiscard]] float GetMilliPerFrame() const;
		
		int m_DesiredFramePerSecond;

	private:
		Timer();
		friend class boop::Singleton<Timer>;

		TimePoint m_StartTime;
		TimePoint m_PreviousTime;
		float m_ElapsedSeconds;
		
		double m_TimeSinceLastFrame;
	};
}

