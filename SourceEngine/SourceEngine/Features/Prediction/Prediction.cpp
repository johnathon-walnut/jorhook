#include "Prediction.h"

int C_LocalPrediction::GetTickbase(C_UserCmd *pCmd, C_BaseEntity *pLocal)
{
	static int nTick = 0;
	static C_UserCmd *pLastCmd = nullptr;

	if (pCmd)
	{
		if (!pLastCmd || pLastCmd->hasbeenpredicted)
		{
			nTick = pLocal->m_nTickBase();
		}
		else
		{
			nTick++;
		}

		pLastCmd = pCmd;
	}

	return nTick;
}

void C_LocalPrediction::Start(C_UserCmd *pCmd)
{
	if (!I::MoveHelper)
	{
		return;
	}

	C_BaseEntity *pLocal = G::EntityCache.pLocal;

	if (pLocal && pLocal->IsAlive())
	{
		pLocal->m_pCurrentCmd() = pCmd;
		
		*I::RandomSeed = MD5_PseudoRandom(pCmd->command_number) & std::numeric_limits<int>::max();

		fOldCurrentTime = I::GlobalVars->curtime;
		fOldFrameTime	= I::GlobalVars->frametime;
		nOldTickCount	= I::GlobalVars->tickcount;
		nOldFlags       = pLocal->m_fFlags();

		const int nOldTickBase				= pLocal->m_nTickBase();
		const bool bOldIsFirstPrediction	= I::Prediction->m_bFirstTimePredicted;
		const bool bOldInPrediction			= I::Prediction->m_bInPrediction;
		
		I::GlobalVars->curtime	= TICKS_TO_TIME(GetTickbase(pCmd, pLocal));
		I::GlobalVars->frametime = (I::Prediction->m_bEnginePaused ? 0.0f : TICK_INTERVAL);
		I::GlobalVars->tickcount = GetTickbase(pCmd, pLocal);

		I::Prediction->m_bFirstTimePredicted = false;
		I::Prediction->m_bInPrediction		= true;

		//skipped buttons

		//TODO: CheckMovingGround(pLocal, I::GlobalVars->frametime);

		I::Prediction->SetLocalViewAngles(pCmd->viewangles);

		I::MoveHelper->SetHost(pLocal);

		I::Prediction->SetupMove(pLocal, pCmd, I::MoveHelper, &moveData);
		I::GameMovement->ProcessMovement(pLocal, &moveData);
		I::Prediction->FinishMove(pLocal, pCmd, &moveData);

		pLocal->m_nTickBase() = nOldTickBase;

		I::Prediction->m_bInPrediction		= bOldInPrediction;
		I::Prediction->m_bFirstTimePredicted = bOldIsFirstPrediction;
	}
}

void C_LocalPrediction::End(C_UserCmd *pCmd)
{
	if (!I::MoveHelper)
	{
		return;
	}

	C_BaseEntity *pLocal = G::EntityCache.pLocal;

	if (pLocal && pLocal->IsAlive())
	{
		I::MoveHelper->SetHost(nullptr);

		I::GlobalVars->curtime	= fOldCurrentTime;
		I::GlobalVars->frametime = fOldFrameTime;
		I::GlobalVars->tickcount = nOldTickCount;
		
		pLocal->m_pCurrentCmd() = nullptr;

		*I::RandomSeed = -1;
	}
}