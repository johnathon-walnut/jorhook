	#include "Hook.h"

#include "../Features/Prediction/Prediction.h"
#include "../Features/Aimbot/Aimbot.h"
#include "../Features/Movement/Movement.h"

MAKE_HOOK(ClientModeShared_CreateMove, GetVFuncPtr(I::ClientMode, 21), bool, __fastcall,
		  void* ecx, void* edx, float input_sample_frametime, C_UserCmd* pCmd)
{
	if (!pCmd || !pCmd->command_number)
		return false;

	uintptr_t _bp; __asm mov _bp, ebp;
	bool* pSendPacket = (bool*)(***(uintptr_t***)_bp - 0x1);

	auto pLocal = G::EntityCache.pLocal;
	auto pWeapon = G::EntityCache.pLocalWeapon;

	if (!pLocal || !pWeapon)
	{
		return CALL_ORIGINAL(ecx, edx, input_sample_frametime, pCmd);
	}

	gGlobalInfo.bWeaponCanShoot = pWeapon->CanShoot(pLocal);

	if (pWeapon->GetSlot() != SLOT_MELEE)
	{
		if (pWeapon->m_bInReload() || pWeapon->m_iReloadMode() != 0)
		{
			gGlobalInfo.bWeaponCanShoot = true;
		}

		if (pWeapon->m_iClip1() == 0)
		{
			gGlobalInfo.bWeaponCanShoot = false;
		}

		if (pLocal->m_iClass() == CLASS_SNIPER && pWeapon->GetSlot() == SLOT_PRIMARY)
		{
			gGlobalInfo.bWeaponCanShoot = true;
		}

		if (pLocal->m_iClass() == CLASS_HEAVY && pWeapon->GetSlot() == SLOT_PRIMARY)
		{
			gGlobalInfo.bWeaponCanShoot = true;
		}
	}

	Vec3  vOldAngles = pCmd->viewangles;
	float flOldSideMove = pCmd->sidemove;
	float flOldForwardMove = pCmd->forwardmove;

	F::Movement.DoBunnyhop(pCmd);
	F::Movement.DoAutostrafe(pLocal, pCmd);

	gGlobalInfo.bSequenceFreezing = !!GetAsyncKeyState(V::Exploits_SequenceFreezing_Key);

	static int oldSequenceNr = 0;

	if (gGlobalInfo.bSequenceFreezing)
	{
		if (pLocal->IsAlive())
		{
			if (auto pNetChannel = I::Engine->GetNetChannelInfo())
			{
				static Vec3 oldOrigin = pLocal->m_vecOrigin();
				oldOrigin = pLocal->m_vecOrigin();
				if (oldSequenceNr != pNetChannel->m_nOutSequenceNr)
				{
					pLocal->m_vecOrigin() = oldOrigin;
				}
				oldSequenceNr = pNetChannel->m_nOutSequenceNr + 1;
				pNetChannel->m_nOutSequenceNr += V::Exploits_SequenceFreezing_Value;
			}
		}
	}

	F::Prediction.Start(pCmd);
	{
		F::Aimbot.Run(pLocal, pWeapon, pCmd);
	}
	F::Prediction.End(pCmd);
	
	if (GetAsyncKeyState(V::Exploits_Anti_Knockback_Key))
	{
		pCmd->forwardmove = 0.0f;
		pCmd->sidemove = 0.0f;

		pCmd->viewangles.y = pLocal->m_vecVelocity().y;
		pCmd->viewangles.x = 90.f;

		F::Aimbot.m_bSilent = true;
	}

	return F::Aimbot.m_bSilent ? false : CALL_ORIGINAL(ecx, edx, input_sample_frametime, pCmd);
}