#include "Utils/HookManager/HookManager.h"

//If you want to make this a mess which has features for many different games
//you need to make this process automated.
//Or then just don't hook WndProc idc

#include "Features/Menu/Menu.h"
#include "Features/Glow/Glow.h"
#include "Features/Chams/Chams.h"

DWORD WINAPI MainThread(LPVOID lpParam)
{
	//Util::InitDebug();

	Sleep(1000);

	I::Steam.Initialize();
	I::Initialize();

	Sleep(1000);

	F::HookManager.Initialize();
	F::Menu.m_Module = reinterpret_cast<HMODULE>(lpParam);

	G::Draw.InitFonts
	({
		//FONT_ESP
		{ 0x0, "Tahoma", 12, 0, FONTFLAG_OUTLINE },
		//FONT_ESP_NAME
		{ 0x0, "Tahoma", 13, 0, FONTFLAG_OUTLINE },
		//FONT_ESP_COND
		{ 0x0, "Consolas", 10, 0, FONTFLAG_OUTLINE },
		//FONT_ESP_PICKUPS
		{ 0x0, "Tahoma", 11, 0, FONTFLAG_OUTLINE },
		//FONT_DEBUG
		{ 0x0, "Arial", 16, 0, FONTFLAG_OUTLINE },
		//FONT_MENU
		{ 0x0, "Segoe UI", 14, 0, FONTFLAG_NONE }
	});

	//CSteamID csLocal = gSteam.User->GetSteamID();
	//csLocal.Render() = Steam ID (STEAM_0:1:201244158)
	//csLocal.SteamRender() = Steam ID3 ([U:1:402488317])

	N::DumpTables();

	/*Util::PrintDebug("MainThread finished.\n");*/

	I::CVars->ConsoleColorPrintf({ 255, 131, 131, 255 }, "[!] jorhook loaded\n");

	//Stuck at this, as long as "panic" key is not pressed.
	while (!(GetAsyncKeyState(VK_F11) & 0x8000))
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	F::Menu.m_Open = false;

	Sleep(100);

	I::CVars->ConsoleColorPrintf({ 255, 242, 131, 255 }, "[!] jorhook unloaded\n");

	F::HookManager.Release();

	if (F::Menu.m_WndProc)
	{
		SetWindowLongW(F::Menu.m_GameHWND, GWL_WNDPROC, reinterpret_cast<LONG>(F::Menu.m_WndProc));
	}

	Sleep(1000);

	F::Chams.Cleanup();
	F::Glow.Cleanup();

	//Util::ReleaseDebug();
	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), EXIT_SUCCESS);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH: {
		if (HANDLE hMain = CreateThread(0, 0, MainThread, hinstDLL, 0, 0)) CloseHandle(hMain);
		break;
	}

	case DLL_PROCESS_DETACH: {
		break;
	}

	default: break;
	}

	return TRUE;
}