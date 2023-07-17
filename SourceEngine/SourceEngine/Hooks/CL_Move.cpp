#include "Hook.h"

#include "../Features/Vars.h"

static int count;

MAKE_HOOK(CL_Move, reinterpret_cast<void*>(G::Pattern.Find("engine.dll", "55 8B EC 83 EC ? 83 3D ? ? ? ? ? 0F 8C ? ? ? ? E8")), void, __cdecl,
		  float cum, bool balls)
{
	if (GetAsyncKeyState(V::Exploits_Airstuck_Key))
	{
		count++;
		return;
		/*if (count != 71)
		{
			return;
		}
		else
		{
			CALL_ORIGINAL(cum, balls);
			return;
		}*/
	}
	
	CALL_ORIGINAL(cum, balls);

	if (GetAsyncKeyState(V::Exploits_Speedhack_Key))
	{
		while (count)
		{
			count--;
			CALL_ORIGINAL(cum, 0);
		}
	}
}

MAKE_HOOK(AdjustPlayerTimeBase, reinterpret_cast<void*>(G::Pattern.Find("server.dll", "55 8B EC 83 EC ? 83 7D ? ? 56 8B F1")), void, __fastcall,
		  void* ecx, void* edx, int simulation_ticks)
{
	gGlobalInfo.nTicks = simulation_ticks;

	CALL_ORIGINAL(ecx, edx, simulation_ticks);
}