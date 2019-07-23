#pragma once

#include "Engine/Subsystem/Subsystem.h"

class CatalystRenderer : Subsystem 
{

public:

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Deinit() override;

private:

	struct GLFWwindow* m_Window;

};