#include "TimerManager.h"

#include "Timer.h"

TimerManager::TimerManager() : m_DeltaTime(0.016f), m_DeltaTimeLogTimer(), m_TimeEnd()
{
}

TimerManager::~TimerManager()
{
	for (size_t i = 0; i < m_Timers.size(); i++)
	{
		if (m_Timers[i]) 
		{
			delete m_Timers[i];
		}
	}
	m_Timers.clear();

	m_DeltaTimeLogTimer.m_OnTimerEnded = nullptr;
	m_DeltaTimeLogTimer.m_Timer = nullptr;
}

void TimerManager::Init()
{

	m_TimeStart = std::chrono::system_clock::now();

	m_DeltaTimeLogTimer = RegisterTimer(5.0f);
	m_DeltaTimeLogTimer.m_OnTimerEnded->Register<TimerManager>(this, &TimerManager::PrintDeltaTime);

	Subsystem::Init();
}

void TimerManager::Tick(float)
{
	m_TimeEnd = std::chrono::system_clock::now() - m_TimeStart;
	m_TimeStart = std::chrono::system_clock::now();
	
	m_DeltaTime = m_TimeEnd.count();
	
	for (Timer* Timer : m_Timers)
	{
		Timer->Tick(m_DeltaTime);
	}
}

void TimerManager::Deinit()
{
	Subsystem::Deinit();
}

float TimerManager::DeltaTime()
{
	return m_DeltaTime;
}

TimerHandle TimerManager::RegisterTimer(float TimerLength, bool bIsLooping, bool bIsPaused)
{
	Timer* NewTimer = new Timer(TimerLength, bIsLooping, bIsPaused);
	TimerHandle ReturnHandle = TimerHandle();
	ReturnHandle.m_Timer = NewTimer;
	ReturnHandle.m_OnTimerEnded = NewTimer->GetTimerEndedEvent();

	m_Timers.push_back(NewTimer);

	return ReturnHandle;
}

void TimerManager::PrintDeltaTime()
{
	printf("DeltaTime: %f\n", m_DeltaTime);
}
