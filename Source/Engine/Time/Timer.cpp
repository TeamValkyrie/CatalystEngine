#include "Timer.h"

Timer::Timer() : m_EventOnTimerEnded(new Event<>()), m_bIsLooping(false), m_bIsPaused(true), m_TimeLeft(0.0f), m_TimerLength(0.0f)
{}

Timer::Timer(float TimerLength, bool bIsLooping) : m_EventOnTimerEnded(new Event<>()), m_bIsLooping(bIsLooping), m_bIsPaused(false), m_TimeLeft(TimerLength), m_TimerLength(TimerLength)
{}

Timer::Timer(float TimerLength, bool bIsLooping, bool bIsPaused) : m_EventOnTimerEnded(new Event<>()), m_bIsLooping(bIsLooping), m_bIsPaused(bIsPaused), m_TimeLeft(TimerLength), m_TimerLength(TimerLength)
{}

Timer::~Timer()
{
	if (m_EventOnTimerEnded) 
	{
		delete m_EventOnTimerEnded;
	}
}

void Timer::Tick(float DeltaTime)
{
	if (!m_bIsPaused) 
	{
		m_TimeLeft -= DeltaTime;
		if (m_TimeLeft <= 0.0f)
		{
			m_EventOnTimerEnded->Dispatch();
			if (m_bIsLooping) 
			{
				Reset();
			}
			else 
			{
				m_bIsPaused = true;
			}
		}
	}
}

void Timer::Start() 
{
	Reset();
	UnPause();
}

void Timer::Reset() 
{
	m_TimeLeft = m_TimerLength;
}

void Timer::Pause()
{
	m_bIsPaused = true;
}

void Timer::UnPause()
{
	m_bIsPaused = false;
}

void Timer::TogglePause()
{
	m_bIsPaused = !m_bIsPaused;
}

void Timer::SetIsLooping(bool bIsLooping)
{
	m_bIsLooping = bIsLooping;
}

void Timer::SetTimerLength(float TimerLength, bool bResetTimer)
{
	m_TimerLength = TimerLength;
	if (bResetTimer) 
	{
		m_TimeLeft = TimerLength;
	}
}

Event<>* Timer::GetTimerEndedEvent()
{
	return m_EventOnTimerEnded;
}
