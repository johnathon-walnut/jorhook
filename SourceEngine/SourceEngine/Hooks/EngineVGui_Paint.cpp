#include "Hook.h"

#include "../Features/Menu/Menu.h"
#include "../Features/ESP/ESP.h"
#include "../Features/Aimbot/Aimbot.h"

MAKE_HOOK(EngineVGui_Paint, GetVFuncPtr(I::EngineVGui, 13), void, __fastcall,
		  void* ecx, void* edx, int mode)
{
	if (!G::ScreenSize.w || !G::ScreenSize.h)
	{
		G::ScreenSize.Update();
		return;
	}

	static auto StartDrawing = reinterpret_cast<void(__thiscall*)(void*)>(G::Pattern.Find("vguimatsurface.dll", "55 8B EC 64 A1 ? ? ? ? 6A FF 68 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 14"));
	static auto FinishDrawing = reinterpret_cast<void(__thiscall*)(void*)>(G::Pattern.Find("vguimatsurface.dll", "55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 51 56 6A 00"));

	//HACK: for some reason we need to do this
	{
		static bool bInitIcons = false;

		if (!bInitIcons)
		{
			for (int n = 0; n < 10; n++)
				G::Draw.Icon(-200, 0, 18, 18, n);

			bInitIcons = true;
		}
	}

	CALL_ORIGINAL(ecx, edx, mode);

	if (mode & PAINT_UIPANELS)
	{
		//let's update WorldToProjection VMatrix here
		{
			C_ViewSetup ViewSetup = {};

			if (I::Client->GetPlayerView(ViewSetup))
			{
				VMatrix WorldToView = {}, ViewToProjection = {}, WorldToPixels = {};
				I::RenderView->GetMatricesForView(ViewSetup, &WorldToView, &ViewToProjection, &gGlobalInfo.WorldToProjection, &WorldToPixels);
			}
		}

		StartDrawing(I::Surface);
		{
			F::ESP.Run();
			F::Menu.Run();
			F::Aimbot.DrawFoVCircle();
		}
		FinishDrawing(I::Surface);
	}
}