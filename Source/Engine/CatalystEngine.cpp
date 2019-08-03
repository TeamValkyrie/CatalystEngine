#include "CatalystEngine.h"

#include "Editor/Tools/Console.h"

#include "Renderer/CatalystRenderer.h"
#include "Renderer/Editor/ImGuiRenderer.h"

#include "Time/TimerManager.h"

#include "imgui.h"

#include <iostream>

CatalystEngine* CTEngine = nullptr;

CatalystEngine::CatalystEngine() : m_Console(nullptr), m_TimerManager(nullptr), m_Renderer(nullptr), bKeepEngineRunning(true), m_bShowEditor(true), m_bShowConsole(false)
{
}

CatalystEngine::~CatalystEngine()
{
}

void CatalystEngine::Init()
{
	printf("Engine: Initialization\n");

	m_Console = new Console();
	m_Console->Init();

	m_TimerManager = new TimerManager();
	m_TimerManager->Init();

	m_Renderer = new CatalystRenderer();
	m_Renderer->Init();

	ImGuiRenderer* ImGuiRenderer = m_Renderer->GetImguiRenderer();
	if (ImGuiRenderer) 
	{
		ImGuiRenderer->GetOnRenderEvent().Register<CatalystEngine>(this, &CatalystEngine::MainMenuBarEditor);
	}

}

void CatalystEngine::Run()
{
	while (bKeepEngineRunning) 
	{
		m_TimerManager->Tick(1.0f);
		TickEngine(m_TimerManager->DeltaTime());
	}
}

void CatalystEngine::Shutdown()
{

	printf("Engine: Shutdown\n");

	m_Renderer->Deinit();
	delete m_Renderer;
}

void CatalystEngine::RequestShutdown()
{
	if (CanEngineShutdown()) 
	{
		bKeepEngineRunning = false;
	}
}

void CatalystEngine::TickEngine(float DeltaTime)
{
	m_Console->Tick(DeltaTime);
	m_Renderer->Tick(DeltaTime);
}

bool CatalystEngine::CanEngineShutdown()
{
	return true;
}

void CatalystEngine::MainMenuBarEditor()
{
	if (m_bShowEditor)
	{
		ImGui::BeginMainMenuBar();

		if(ImGui::BeginMenu("Tools"))
		{
			m_TimerManager->TimerManagerMenuItem();

			if (ImGui::MenuItem("Console", ""))
			{
				m_bShowConsole = !m_bShowConsole;
			}

			ImGui::EndMenu();
		}

		m_TimerManager->TimerManagerWindow();

		m_Console->Draw("Console", &m_bShowConsole);

		ImGui::EndMainMenuBar();
	}
}
