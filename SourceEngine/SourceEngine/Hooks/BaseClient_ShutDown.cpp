#include "Hook.h"

#include "../Features/Glow/Glow.h"
#include "../Features/Chams/Chams.h"

MAKE_HOOK(BaseClient_ShutDown, GetVFuncPtr(I::Client, 7), void, __fastcall,
		  void* ecx, void* edx)
{
	G::EntityCache.Clear();
	F::Glow.Cleanup();
	F::Chams.Cleanup();
}