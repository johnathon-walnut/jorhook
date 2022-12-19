#include "Interface.h"

#undef interface

PVOID CInterface::Get(PCCH szModule, PCCH szObject)
{
	HMODULE hModule = GetModuleHandleA(szModule);
	if (hModule)
	{
		auto CreateInterface = reinterpret_cast<void* (__cdecl*)(const char* name, int* returnCode)>(GetProcAddress(hModule, "CreateInterface"));
		int returnCode = 0;
		void* interface = CreateInterface(szObject, &returnCode);
		if (interface)
		{
			return interface;
		}
	}
	return nullptr;
}