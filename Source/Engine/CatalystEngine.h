#pragma once

class CatalystEngine
{

public:

	CatalystEngine();
	~CatalystEngine();
	CatalystEngine(const CatalystEngine& Other) = delete;

	void Init();
	void Run();
	void Shutdown();

	void RequestShutdown();

private:

	void TickEngine(float DeltaTime);

	bool CanEngineShutdown();

private:

	class CatalystRenderer* m_Renderer;

	bool bKeepEngineRunning;

};

extern CatalystEngine* CTEngine;