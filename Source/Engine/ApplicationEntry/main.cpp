
#include "Engine/CatalystEngine.h"

#include <iostream>

int main() 
{

	CTEngine = new CatalystEngine();
	CTEngine->Init();
	CTEngine->Run();
	CTEngine->Shutdown();

	delete CTEngine;

	return 0;
}