#include "Hook.h"

#include "../Features/Vars.h"

int s_Counter = 0;

MAKE_HOOK(CL_Move, reinterpret_cast<void*>(G::Pattern.Find("engine.dll", "55 8B EC 83 EC ? 83 3D ? ? ? ? ? 0F 8C ? ? ? ? E8")), void, __cdecl,
		  float cum, bool balls)
{
	if (GetAsyncKeyState(V::Exploits_Airstuck_Key))
	{
		s_Counter++;
		if (s_Counter != 71)
		{
			return;
		}
		else
		{
			s_Counter = 0;
		}
	}
	CALL_ORIGINAL(cum, balls);
}