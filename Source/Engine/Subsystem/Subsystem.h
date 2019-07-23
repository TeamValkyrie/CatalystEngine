#pragma once

/*
* Subsystem interface used for standardising Subsystem layout
*/
class Subsystem 
{

public:

	Subsystem();
	virtual ~Subsystem();

	virtual void Init();
	virtual void Tick(float DeltaTime) = 0;
	virtual void Deinit();

	bool IsInitialized();

private:

	bool m_bIsInitialized;

};