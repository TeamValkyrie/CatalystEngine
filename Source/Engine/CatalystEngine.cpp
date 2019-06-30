#include "CatalystEngine.h"

CatalystEngine::CatalystEngine() : bKeepEngineRunning(true)
{

}

CatalystEngine::~CatalystEngine()
{

}

void CatalystEngine::Init()
{

}

void CatalystEngine::Run()
{
	while (bKeepEngineRunning) 
	{
		TickEngine(1.0f);
	}
}

void CatalystEngine::Shutdown()
{

}

void CatalystEngine::RequestShutdown()
{

}

void CatalystEngine::TickEngine(float)
{
}
