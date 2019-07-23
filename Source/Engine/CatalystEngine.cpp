#include "CatalystEngine.h"

#include "Renderer/CatalystRenderer.h"

CatalystEngine::CatalystEngine() : m_Renderer(nullptr), bKeepEngineRunning(true)
{

}

CatalystEngine::~CatalystEngine()
{

}

void CatalystEngine::Init()
{
	m_Renderer = new CatalystRenderer();
	m_Renderer->Init();
}

void CatalystEngine::Run()
{
	while (bKeepEngineRunning) 
	{
		TickEngine(1.0f);
		m_Renderer->Tick(1.0f);
	}
}

void CatalystEngine::Shutdown()
{
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

void CatalystEngine::TickEngine(float)
{

}

bool CatalystEngine::CanEngineShutdown()
{
	return true;
}
