#include "BaseCombatWeapon.h"

bool C_BaseCombatWeapon::CanShoot(C_BaseEntity* pLocal)
{
	if (auto pNet = I::Engine->GetNetChannelInfo())
	{
		static auto cl_interp = I::CVars->FindVar("cl_interp");
		float fInterp = cl_interp->GetFloat();
		float fLatency = (pNet->GetLatency(FLOW_OUTGOING) + pNet->GetLatency(FLOW_INCOMING));

		return (m_flNextPrimaryAttack() < (static_cast<float>(pLocal->m_nTickBase() + (fInterp + fLatency)) * I::GlobalVars->interval_per_tick));
	}
	
	return false;
}

bool C_BaseCombatWeapon::CanSecondaryAttack(C_BaseEntity* pLocal)
{
	return (m_flNextSecondaryAttack() < (static_cast<float>(pLocal->m_nTickBase()) * I::GlobalVars->interval_per_tick));
}

int C_BaseCombatWeapon::GetSlot()
{
	static auto FN = reinterpret_cast<int(__thiscall*)(PVOID)>(G::Pattern.Find("client.dll", "0F B7 81 ? ? ? ? 50 E8 ? ? ? ? 83 C4 ? 8B 80 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC 8B 81 ? ? ? ? 81 C1"));
	return FN(this);
}
