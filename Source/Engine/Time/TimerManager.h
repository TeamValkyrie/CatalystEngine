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
	float FPS();

	TimerHandle RegisterTimer(float TimerLength, bool bIsLooping = true, bool bIsPaused = false);
	
	void TimerManagerMenuItem();
	void TimerManagerWindow();
	void LogDeltaTime();

	void SetDeltaTimeLogInterval(float LogInterval);

	float AverageDeltaTime();
	float AverageFPS();
	
private:

	float m_DeltaTime;
	float m_MinDeltaTime;
	float m_MaxDeltaTime;

	std::vector<class Timer*> m_Timers;

	std::chrono::system_clock::time_point m_TimeStart;
	std::chrono::duration<float> m_TimeEnd;

	TimerHandle m_DeltaTimeLogTimer;
	std::vector<float> m_DeltaTimeLogContainer;
	bool m_bShowDeltaTimeLogWindow;

	int m_FrameCounter;

};