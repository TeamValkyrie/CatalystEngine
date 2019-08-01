#include "TimerManager.h"

#include "Timer.h"

#include "imgui.h"

#include <limits>

TimerManager::TimerManager() : m_DeltaTime(0.016f), m_MinDeltaTime(std::numeric_limits<float>::max()), m_MaxDeltaTime(std::numeric_limits<float>::min()), m_TimeEnd(), m_DeltaTimeLogTimer(), m_bShowDeltaTimeLogWindow(false), m_FrameCounter(0)
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

	m_DeltaTimeLogTimer = RegisterTimer(1.0f);
	m_DeltaTimeLogTimer.m_OnTimerEnded->Register<TimerManager>(this, &TimerManager::LogDeltaTime);

	Subsystem::Init();
}

void TimerManager::Tick(float)
{
	m_FrameCounter++;

	m_TimeEnd = std::chrono::system_clock::now() - m_TimeStart;
	m_TimeStart = std::chrono::system_clock::now();
	
	m_DeltaTime = m_TimeEnd.count();
	
	for (Timer* Timer : m_Timers)
	{
		Timer->Tick(m_DeltaTime);
	}

	if (m_FrameCounter > 1) 
	{
		if (m_DeltaTime > m_MaxDeltaTime)
		{
			m_MaxDeltaTime = m_DeltaTime;
			LogDeltaTime();
			return;
		}
		else if (m_DeltaTime < m_MinDeltaTime)
		{
			LogDeltaTime();
			m_MinDeltaTime = m_DeltaTime;
			return;
		}
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

float TimerManager::FPS()
{
	if (m_DeltaTime != 0.0f) 
	{
		return 1.0f / m_DeltaTime;
	}
	return -1.0f;
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

void TimerManager::TimerManagerMenuItem()
{

	if (ImGui::MenuItem("TimerManager", ""))
	{
		m_bShowDeltaTimeLogWindow = !m_bShowDeltaTimeLogWindow;
	}

}

void TimerManager::TimerManagerWindow()
{
	if (m_bShowDeltaTimeLogWindow)
	{
		if (ImGui::Begin("TimerManager", &m_bShowDeltaTimeLogWindow))
		{
			ImGui::SetWindowSize(ImVec2(250, 250), ImGuiCond_FirstUseEver);
			ImGui::SetWindowPos(ImVec2(250, 250), ImGuiCond_FirstUseEver);
			ImGui::Text("DT: %f ms, FPS: %f", m_DeltaTime, FPS());
			ImGui::Text("Delta Time (ms) Graph");

			if (m_DeltaTimeLogContainer.size() > 0) 
			{
				ImGui::PlotLines(
					"", 
					&m_DeltaTimeLogContainer[0], 
					static_cast<int>(m_DeltaTimeLogContainer.size()),
					0,
					nullptr,
					m_MinDeltaTime,
					m_MaxDeltaTime,
					ImVec2(ImGui::GetContentRegionAvailWidth(),100));

				ImGui::Text("Avg DT: %f ms", AverageDeltaTime());
				ImGui::Text("Avg FPS: %f", AverageFPS());

			}

			ImGui::Text("Min DT: %f ms", m_MinDeltaTime);
			ImGui::Text("Max DT: %f ms", m_MaxDeltaTime);
		}
		ImGui::End();
	}
}

void TimerManager::LogDeltaTime()
{
	m_DeltaTimeLogContainer.push_back(m_DeltaTime);
}

void TimerManager::SetDeltaTimeLogInterval(float LogInterval)
{
	m_DeltaTimeLogTimer.m_Timer->SetTimerLength(LogInterval, true);
}

float TimerManager::AverageDeltaTime()
{
	float Average= 0.0f;
	for (float Ms : m_DeltaTimeLogContainer)
	{
		Average += Ms;
	}
	return Average / m_DeltaTimeLogContainer.size();
}

float TimerManager::AverageFPS()
{
	float AvgDeltaTime = AverageDeltaTime();
	if (AvgDeltaTime != 0)
	{
		return 1 / AvgDeltaTime;
	}

	return -1;
}
