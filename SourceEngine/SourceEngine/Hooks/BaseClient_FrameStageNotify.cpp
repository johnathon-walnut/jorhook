#include "Hook.h"

MAKE_HOOK(BaseClient_FrameStageNotify, GetVFuncPtr(I::Client, 35), void, __fastcall,
		  void* ecx, void* edx, ClientFrameStage_t curStage)
{
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