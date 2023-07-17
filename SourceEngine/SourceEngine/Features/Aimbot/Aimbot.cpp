#include "Aimbot.h"

struct Target_t
{
	int nIndex;
	C_BaseEntity* pEntity;
	Vec3 aimedBonePosition;
	Vec3 angleTo;
	float fovTo;
};

int s_OldButtons = 0;

void CAimbot::Run(C_BaseEntity* pLocal, C_BaseCombatWeapon* pWeapon, C_UserCmd* pCmd)
{

	m_bSilent = false;

	if (pLocal->deadflag())
	{
		return;
	}

	if (!GetAsyncKeyState(V::Aimbot_AimKey))
	{
		gGlobalInfo.nCurrentTargetIdx = -1;
		return;
	}

	int nLocalClass = pLocal->m_iClass();

	s_OldButtons = pCmd->buttons;

	if (nLocalClass == CLASS_SNIPER && pWeapon->GetSlot() == SLOT_PRIMARY)
	{
		pCmd->buttons |= IN_ATTACK;
	}

	std::vector<Target_t> vecPlayers;

	for (const auto& pEntity : G::EntityCache.GetGroup(GroupType_t::PLAYERS_ENEMIES))
	{
		if (pEntity->deadflag() || pEntity->IsDormant() || pEntity == pLocal)
		{
			continue;
		}

		if (pWeapon->GetSlot() == SLOT_MELEE)
		{
			if (pLocal->GetWorldSpaceCenter().DistTo(pEntity->GetWorldSpaceCenter()) > 70.f)
			{
				continue;
			}
		}

		Target_t target = {};
		target.pEntity = pEntity;
		target.nIndex = pEntity->entindex();
		switch (V::Aimbot_Hitbox)
		{
			case 0: //auto
			default:
			{
				if (nLocalClass == CLASS_SNIPER && pWeapon->GetSlot() == SLOT_PRIMARY)
				{
					target.aimedBonePosition = pEntity->GetHitboxPos(HITBOX_HEAD);
				}
				else
				{
					target.aimedBonePosition = pEntity->GetHitboxPos(HITBOX_PELVIS);
				}
				break;
			}
			case 1:
			{
				target.aimedBonePosition = pEntity->GetHitboxPos(HITBOX_HEAD);
				break;
			}
			case 2:
			{
				target.aimedBonePosition = pEntity->GetHitboxPos(HITBOX_PELVIS);
				break;
			}
		}

		target.angleTo = Math::CalcAngle(pLocal->m_vecOrigin() + pLocal->m_vecViewOffset(), target.aimedBonePosition);
		if (!gGlobalInfo.vecPunchAngles.IsZero())
		{
			target.angleTo -= gGlobalInfo.vecPunchAngles;
		}
		target.fovTo = Math::CalcFov(pCmd->viewangles, target.angleTo);

		vecPlayers.push_back(target);
	}

	std::sort(vecPlayers.begin(), vecPlayers.end(), [](const Target_t& a, const Target_t& b) -> bool
			  {
				  return (a.fovTo < b.fovTo);
			  });

	auto cl_interp = I::CVars->FindVar("cl_interp");
	auto cl_interp_ratio = I::CVars->FindVar("cl_interp_ratio");
	auto cl_cmdrate = I::CVars->FindVar("cl_cmdrate");

	if (vecPlayers.empty())
	{
		gGlobalInfo.nCurrentTargetIdx = -1;
	}

	for (const auto& target : vecPlayers)
	{
		if (target.fovTo > V::Aimbot_FoV)
		{
			continue;
		}

		if (!G::VisCheck.Pos(pLocal, target.pEntity, pLocal->m_vecOrigin() + pLocal->m_vecViewOffset(), target.aimedBonePosition))
		{
			continue;
		}

		m_AimedAngle = target.angleTo;

		if (gGlobalInfo.bWeaponCanShoot)
		{
			pCmd->tick_count = TIME_TO_TICKS(target.pEntity->m_flSimulationTime()) + std::max(cl_interp->GetFloat(), cl_interp_ratio->GetFloat() / cl_cmdrate->GetFloat());
			if (nLocalClass == CLASS_SNIPER && pWeapon->GetSlot() == SLOT_PRIMARY)
			{
				pCmd->buttons &= ~IN_ATTACK;
			}
			else
			{
				pCmd->buttons |= IN_ATTACK;
			}
			Vec3 vecMove(pCmd->forwardmove, pCmd->sidemove, pCmd->upmove);
			Vec3 vecMoveAng = Vec3();

			Math::VectorAngles(vecMove, vecMoveAng);

			float fSpeed = Math::FastSqrt(vecMove.x * vecMove.x + vecMove.y * vecMove.y);
			float fYaw = DEG2RAD(target.angleTo.y - pCmd->viewangles.y + vecMoveAng.y);

			pCmd->forwardmove = (cos(fYaw) * fSpeed);
			pCmd->sidemove = (sin(fYaw) * fSpeed);

			pCmd->viewangles = target.angleTo;

			I::DebugOverlay->AddBoxOverlay(target.aimedBonePosition, { -2,-2,-2 }, { 2,2,2 }, { 0,0,0 }, 255, 0, 0, 255, 1.0f);
			m_bSilent = true;

			gGlobalInfo.nCurrentTargetIdx = target.nIndex;

			return;
		}

	}
}

void CAimbot::DrawFoVCircle()
{
	if (!V::Misc_Show_Aimbot_FoV)
	{
		return;
	}

	const float flFOV = static_cast<float>(V::Misc_FoV);
	const float flR = tanf(DEG2RAD(V::Aimbot_FoV) / 2.0f) / tanf(DEG2RAD(flFOV) / 2.0f) * G::ScreenSize.w;
	G::Draw.OutlinedCircle(G::ScreenSize.w / 2, G::ScreenSize.h / 2, flR, 68, V::Colors_OutlineColor);
}
