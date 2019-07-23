#include "Subsystem.h"

Subsystem::Subsystem() : m_bIsInitialized(false)
{

}

Subsystem::~Subsystem()
{
	if (m_bIsInitialized) 
	{
		Deinit();
	}
}

void Subsystem::Init()
{
	m_bIsInitialized = true;
}

void Subsystem::Deinit()
{
	m_bIsInitialized = false;
}

bool Subsystem::IsInitialized()
{
	return m_bIsInitialized;
}
