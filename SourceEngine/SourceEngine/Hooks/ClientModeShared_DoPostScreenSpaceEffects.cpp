#include "Hook.h"

#include "../Features/Glow/Glow.h"
#include "../Features/Chams/Chams.h"

MAKE_HOOK(ClientModeShared_DoPostScreenSpaceEffects, GetVFuncPtr(I::ClientMode, 39), bool, __fastcall,
		  void* ecx, void* edx, const C_ViewSetup* pView)
{
	F::Chams.Run();
	F::Glow.Run();
	return CALL_ORIGINAL(ecx, edx, pView);
}