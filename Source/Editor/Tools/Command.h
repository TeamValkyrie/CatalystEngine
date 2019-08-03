#pragma once

#include <Events/EventDispatching.h>

template<typename... Args>
class Command : public Event<Args...>
{

public:

	void SetCommandName(const char* CommandName) 
	{
		m_CommandName = CommandName;
	}

	const char* GetCommandName() 
	{
		return m_CommandName;
	}

private:

	const char* m_CommandName;

};

