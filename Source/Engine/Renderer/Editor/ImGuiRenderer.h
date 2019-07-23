#pragma once

#include "Engine/Subsystem/Subsystem.h"

#include <Events/EventDispatching.h>

class ImGuiRenderer : public Subsystem 
{

public:

	ImGuiRenderer();

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Deinit() override;

	Event<>& GetOnRenderEvent();

private:

	struct GLFWwindow* m_Window;

	Event<> m_OnRenderEvent;

};