#include "Hook.h"

MAKE_HOOK(Prediction_RunCommand, GetVFuncPtr(I::Prediction, 17), void, __fastcall,
		  void* ecx, void* edx, C_BaseEntity* pEntity, C_UserCmd* pCmd, C_MoveHelper* pMoveHelper)
{
	CALL_ORIGINAL(ecx, edx, pEntity, pCmd, pMoveHelper);

	if (pMoveHelper && !I::MoveHelper)
	{
		I::MoveHelper = pMoveHelper;
	}
}