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