#include "Hook.h"

#include "../Features/Vars.h"

MAKE_HOOK(BaseClient_FrameStageNotify, GetVFuncPtr(I::Client, 35), void, __fastcall,
		  void* ecx, void* edx, ClientFrameStage_t curStage)
{
	switch (curStage)
	{
		case ClientFrameStage_t::FRAME_RENDER_START:
		{
			gGlobalInfo.vecPunchAngles = Vec3();

			if (const auto& pLocal = G::EntityCache.pLocal)
			{
				gGlobalInfo.vecPunchAngles = pLocal->m_vecPunchAngle();
				if (V::Misc_Remove_Visual_Punch)
				{
					pLocal->m_vecPunchAngle() = Vec3(0.0f, 0.0f, 0.0f);
				}
			}
		}
	}

	CALL_ORIGINAL(ecx, edx, curStage);

	switch (curStage)
	{
		case ClientFrameStage_t::FRAME_NET_UPDATE_START:
		{
			G::EntityCache.Clear();
			break;
		}

		case ClientFrameStage_t::FRAME_NET_UPDATE_END:
		{
			G::EntityCache.Fill();
			break;
		}
	}
}