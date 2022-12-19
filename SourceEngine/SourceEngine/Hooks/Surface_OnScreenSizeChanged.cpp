#include "Hook.h"

MAKE_HOOK(Surface_OnScreenSizeChanged, GetVFuncPtr(I::Surface, 111), void, __fastcall,
		  void* ecx, void* edx, int nOldWidth, int nOldHeight)
{
	CALL_ORIGINAL(ecx, edx, nOldWidth, nOldHeight);

	G::ScreenSize.Update();
	G::Draw.ReloadFonts();
}