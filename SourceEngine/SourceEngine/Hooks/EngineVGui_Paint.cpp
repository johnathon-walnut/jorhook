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

			G::Draw.StringCenter(FONT_MENU, G::ScreenSize.w / 2, G::ScreenSize.h / 2, { 255,255,255,255 }, "Ticks: %d", gGlobalInfo.nTicks);

			if (const auto& pLocal = G::EntityCache.pLocal)
			{
				if (pLocal->IsAlive())
				{
					const Vec3& vecLocalPos = pLocal->m_vecOrigin();

					for (const auto& Enemy : G::EntityCache.GetGroup(GroupType_t::PLAYERS_ENEMIES))
					{
						if (Enemy->deadflag())
							continue;

						if (Enemy->m_iClass() == CLASS_SPY)
						{
							if (Enemy->m_vecOrigin().DistTo(vecLocalPos) < 400)
							{
								if (G::VisCheck.Pos(pLocal, Enemy, pLocal->m_vecOrigin(), Enemy->m_vecOrigin()))
								{
									G::Draw.Rect(0, 0, G::ScreenSize.w, G::ScreenSize.h, { 255,0,0,100 });
								}
							}
						}
					}
				}
			}

			
		}
		FinishDrawing(I::Surface);
	}
}