#pragma once

#include "../Vars.h"

class CAimbot
{
public:
	void Run(C_BaseEntity* pLocal, C_BaseCombatWeapon* pWeapon, C_UserCmd* pCmd);
	void DrawFoVCircle();
	bool m_bSilent = false;

	Vec3 m_AimedAngle;
};

MAKE_FEATURE(CAimbot, Aimbot);