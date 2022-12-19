#include "Hook.h"

MAKE_HOOK(BaseClient_ShutDown, GetVFuncPtr(I::Client, 7), void, __fastcall,
		  void* ecx, void* edx)
{
	G::EntityCache.Clear();
}