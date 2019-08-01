#pragma once

#include "Engine/Subsystem/Subsystem.h"

#include "TimerHandle.h"

#include <vector>
#include <chrono>

class TimerManager : public Subsystem
{

public:

	TimerManager();
	virtual ~TimerManager();

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Deinit() override;

	float DeltaTime();

	TimerHandle RegisterTimer(float TimerLength, bool bIsLooping = true, bool bIsPaused = false);
	 
	void PrintDeltaTime();

private:

	float m_DeltaTime;

	TimerHandle m_DeltaTimeLogTimer;

	std::vector<class Timer*> m_Timers;

	std::chrono::system_clock::time_point m_TimeStart;
	std::chrono::duration<float> m_TimeEnd;
};