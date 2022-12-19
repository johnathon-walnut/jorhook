#include "Hook.h"

#include "../Features/Menu/Menu.h"

MAKE_HOOK(Surface_LockCursor, GetVFuncPtr(I::Surface, 62), void, __fastcall,
		  void* ecx, void* edx)
{
	F::Menu.m_Open ? I::Surface->UnlockCursor() : CALL_ORIGINAL(ecx, edx);
}