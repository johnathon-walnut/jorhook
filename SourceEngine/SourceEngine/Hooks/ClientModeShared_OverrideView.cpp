#include "Hook.h"

#include "../Features/Vars.h"

MAKE_HOOK(ClientModeShared_OverrideView, GetVFuncPtr(I::ClientMode, 16), void, __fastcall,
		  void* ecx, void* edx, C_ViewSetup* pView)
{
	CALL_ORIGINAL(ecx, edx, pView);

	pView->fov = V::Misc_FoV;
}