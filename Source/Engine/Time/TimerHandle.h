#pragma once

#include <Events/EventDispatching.h>

struct TimerHandle
{
	class Timer* m_Timer;
	Event<>* m_OnTimerEnded;
};