#pragma once

#include "Engine/Subsystem/Subsystem.h"

class InputManager : public Subsystem 
{

public:

	InputManager();
	virtual ~InputManager();

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Deinit() override;

private:



};