#include "Hook.h"
#include "../Features/Vars.h"

MAKE_HOOK(CTFPlayer_AvoidPlayers, reinterpret_cast<void*>(G::Pattern.Find("client.dll", "55 8B EC 81 EC ? ? ? ? 8B 45 ? 89 45")), void, __fastcall,
		  void* ecx, void* edx, C_UserCmd* pCmd)
{
	if (V::Movement_NoPush)
	{
		return;
	}
	CALL_ORIGINAL(ecx, edx, pCmd);
}