#include "Hook.h"

#include "../Features/Vars.h"

MAKE_HOOK(ClientModeShared_OverrideView, GetVFuncPtr(I::ClientMode, 16), void, __fastcall,
		  void* ecx, void* edx, C_ViewSetup* pView)
{
	CALL_ORIGINAL(ecx, edx, pView);

	pView->fov = V::Misc_FoV;

	auto local = G::EntityCache.pLocal;

	if (!local)
		return;

	static bool thirdperson = false;

	if (GetAsyncKeyState(V::Visuals_Thirdperson_Key) & 0x1)
	{
		thirdperson = !thirdperson;
	}

	bool taunting = local->m_nPlayerCond() & 128;

	if (taunting) // if taunting
		thirdperson = true;

	if (!thirdperson && !taunting)
		local->m_nForceTauntCam() = 0;

	if (thirdperson || taunting)
		local->m_nForceTauntCam() = 1;
}