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

	void RequestShutdown(int NumArgs, char* Args[]);

private:

	void TickEngine(float DeltaTime);

	bool CanEngineShutdown();

	void MainMenuBarEditor();

private:

	class Console* m_Console;
	class TimerManager* m_TimerManager;
	class CatalystRenderer* m_Renderer;

	bool bKeepEngineRunning;

	bool m_bShowEditor;
	bool m_bShowConsole;

};

extern CatalystEngine* CTEngine;