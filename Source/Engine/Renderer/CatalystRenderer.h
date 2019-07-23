#pragma once

#include "Engine/Subsystem/Subsystem.h"

class CatalystRenderer : public Subsystem 
{

public:

	virtual ~CatalystRenderer();

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Deinit() override;

	class ImGuiRenderer* GetImguiRenderer();

private:

	struct GLFWwindow* m_Window;

	class ImGuiRenderer* m_ImGuiRenderer;

};