
#include <cstdint>

void* __cdecl operator new[](size_t size, const char* /*name*/, int /*flags*/, unsigned /*debugFlags*/, const char* /*file*/, int /*line*/) 
{
	return new uint8_t[size];
}
