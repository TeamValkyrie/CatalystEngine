#pragma once

#include <Events/EventDispatching.h>

class Timer 
{

public:

	Timer();
	Timer(float TimerLength, bool bIsLooping);
	Timer(float TimerLength, bool bIsLooping, bool bIsPaused);
	
	virtual ~Timer();

	void Tick(float DeltaTime);

	void Start();
	void Reset();

	void Pause();
	void UnPause();
	void TogglePause();

	void SetIsLooping(bool bIsLooping);

	void SetTimerLength(float TimerLength, bool bResetTimer = false);

	Event<>* GetTimerEndedEvent();

private:

	Event<>* m_EventOnTimerEnded;

	bool m_bIsLooping;
	bool m_bIsPaused;

	float m_TimerLength;
	float m_TimeLeft;

};