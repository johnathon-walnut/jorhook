#include "Movement.h"

void CMovement::DoBunnyhop(C_UserCmd* pCmd)
{
	if (auto pLocal{ G::EntityCache.pLocal })
	{
		if (!V::Movement_Bunnyhop || !pLocal->IsAlive())
		{
			return;
		}

		static bool bJumpState = false;

		if (pCmd->buttons & IN_JUMP)
		{
			if (!bJumpState && !pLocal->IsOnGround())
			{
				pCmd->buttons &= ~IN_JUMP;
			}

			else if (bJumpState)
			{
				bJumpState = false;
			}
		}

		else if (!bJumpState)
		{
			bJumpState = true;
		}
	}
}

void CMovement::DoAutostrafe(C_BaseEntity* pLocal, C_UserCmd* cmd)
{
	if (!V::Movement_AutoStrafe)
	{
		return;
	}

	if (pLocal->m_fFlags() &FL_ONGROUND)
	{
		return;
	}

	if (!(cmd->buttons & (IN_MOVELEFT | IN_MOVERIGHT | IN_FORWARD | IN_BACK)))
	{
		return;
	}

	float oldfmove = cmd->forwardmove;
	float oldsmove = cmd->sidemove;

	Vec3 forward = {}, right = {};
	Math::AngleVectors(cmd->viewangles, &forward, &right, nullptr);

	forward.z = right.z = 0.0f;

	forward.Normalize();
	right.Normalize();

	Vec3 wishdir = {};
	Math::VectorAngles({ (forward.x * oldfmove) + (right.x * oldsmove), (forward.y * oldfmove) + (right.y * oldsmove), 0.0f }, wishdir);

	Vec3 curdir = {};
	Math::VectorAngles(pLocal->m_vecVelocity(), curdir);

	float directiondelta = Math::NormalizeAngle(wishdir.y - curdir.y);
	const float turnscale = Math::RemapValClamped(V::Movement_AutoStrafe_TurnScale, 0.0f, 1.0f, 0.9f, 1.0f);
	float rotation = DEG2RAD((directiondelta > 0.0f ? -90.0f : 90.f) + (directiondelta * turnscale));

	float cosrotation = cosf(rotation);
	float sinrotation = sinf(rotation);

	cmd->forwardmove = (cosrotation * oldfmove) - (sinrotation * oldsmove);
	cmd->sidemove = (sinrotation * oldfmove) + (cosrotation * oldsmove);
}
