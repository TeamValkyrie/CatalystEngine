#pragma once

#include "Engine/Subsystem/Subsystem.h"

class ImGuiRenderer : public Subsystem 
{

public:

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Deinit() override;

private:

	struct GLFWwindow* m_Window;

};