#include "Interfaces.h"

#define CHECKNULL(func) assert(func != nullptr)

#define CLIENT_DLL		"client.dll"
#define ENGINE_DLL		"engine.dll"
#define SERVER_DLL		"server.dll"
#define VGUI2_DLL		"vgui2.dll"
#define MATSURFACE_DLL	"vguimatsurface.dll"
#define VSTDLIB_DLL		"vstdlib.dll"
#define STEAMCLIENT_DLL "SteamClient.dll"
#define MATSYSTEM_DLL	"MaterialSystem.dll"

void I::Initialize()
{
	Client = reinterpret_cast<C_BaseClientDLL*>(G::Interface.Get(CLIENT_DLL, CLIENT_DLL_INTERFACE_VERSION));
	CHECKNULL(Client);

	ClientShared = reinterpret_cast<C_ClientDLLSharedAppSystems*>(G::Interface.Get(CLIENT_DLL, CLIENT_DLL_SHARED_APPSYSTEMS));
	CHECKNULL(ClientShared);

	EntityList = reinterpret_cast<C_ClientEntityList*>(G::Interface.Get(CLIENT_DLL, VCLIENTENTITYLIST_INTERFACE_VERSION));
	CHECKNULL(EntityList);

	Prediction = reinterpret_cast<C_Prediction*>(G::Interface.Get(CLIENT_DLL, VCLIENT_PREDICTION_INTERFACE_VERSION));
	CHECKNULL(Prediction);

	GameMovement = reinterpret_cast<C_GameMovement*>(G::Interface.Get(CLIENT_DLL, CLIENT_GAMEMOVEMENT_INTERFACE_VERSION));
	CHECKNULL(GameMovement);

	ModelInfo = reinterpret_cast<C_ModelInfoClient*>(G::Interface.Get(ENGINE_DLL, VMODELINFO_CLIENT_INTERFACE_VERSION));
	CHECKNULL(ModelInfo);

	Engine = reinterpret_cast<C_EngineClient*>(G::Interface.Get(ENGINE_DLL, VENGINE_CLIENT_INTERFACE_VERSION_13));
	CHECKNULL(Engine);

	EngineTrace = reinterpret_cast<C_EngineTrace*>(G::Interface.Get(ENGINE_DLL, VENGINE_TRACE_CLIENT_INTERFACE_VERSION));
	CHECKNULL(EngineTrace);

	Panel = reinterpret_cast<C_Panel*>(G::Interface.Get(VGUI2_DLL, VGUI_PANEL_INTERFACE_VERSION));
	CHECKNULL(Panel);

	Surface = reinterpret_cast<C_Surface*>(G::Interface.Get(MATSURFACE_DLL, VGUI_SURFACE_INTERFACE_VERSION));
	CHECKNULL(Surface);

	CVars = reinterpret_cast<ICvar*>(G::Interface.Get(VSTDLIB_DLL, VENGINE_CVAR_INTERFACE_VERSION));
	CHECKNULL(CVars);

	GlobalVars = *reinterpret_cast<C_GlobalVarsBase**>(G::Pattern.Find(ENGINE_DLL, "A1 ? ? ? ? 8B 11 68") + 0x8);
	CHECKNULL(GlobalVars);

	void* ClientTable = reinterpret_cast<void*>(G::Pattern.Find(CLIENT_DLL, "8B 0D ? ? ? ? 8B 01 5D FF 60 28 CC"));
	CHECKNULL(ClientTable);

	ClientMode = **reinterpret_cast<C_ClientModeShared***>(reinterpret_cast<DWORD>(ClientTable) + 2);
	CHECKNULL(ClientMode);

	EngineVGui = reinterpret_cast<C_EngineVGui*>(G::Interface.Get(ENGINE_DLL, VENGINE_VGUI_VERSION));
	CHECKNULL(EngineVGui);

	RandomSeed = *reinterpret_cast<int32_t**>(G::Pattern.Find(CLIENT_DLL, "C7 05 ? ? ? ? ? ? ? ? 5D C3 8B 40 34") + 0x2);
	CHECKNULL(RandomSeed);

	DemoPlayer = **reinterpret_cast<void***>(G::Pattern.Find(ENGINE_DLL, "8B 0D ? ? ? ? 85 C9 74 3B 8B 01 8B 40 18 FF D0 84 C0 74 30") + 0x2);
	CHECKNULL(DemoPlayer);

	GameEvent = reinterpret_cast<C_GameEventManager*>(G::Interface.Get(ENGINE_DLL, GAMEEVENTSMANAGER_ENGINE_INTERFACE));
	CHECKNULL(GameEvent);

	RenderView = reinterpret_cast<C_RenderView*>(G::Interface.Get(ENGINE_DLL, VENGINE_RENDERVIEW_INTERFACE_VERSION));
	CHECKNULL(RenderView);

	DebugOverlay = reinterpret_cast<IDebugOverlay*>(G::Interface.Get(ENGINE_DLL, VENGINE_DEBUGOVERLAY_INTERFACE_VERSION));
	CHECKNULL(RenderView);

	MatSystemSurface = reinterpret_cast<IMatSystemSurface*>(G::Interface.Get(MATSURFACE_DLL, VGUI_SURFACE_INTERFACE_VERSION));
	CHECKNULL(MatSystemSurface);

	MaterialSystem = reinterpret_cast<IMaterialSystem*>(G::Interface.Get(MATSYSTEM_DLL, MATERIAL_SYSTEM_INTERFACE_VERSION));
	CHECKNULL(MaterialSystem);

	ModelRender = reinterpret_cast<CModelRender*>(G::Interface.Get(ENGINE_DLL, VENGINE_MODELRENDER_INTERFACE));
	CHECKNULL(ModelRender);
}

void C_SteamInterfaces::Initialize()
{
	Client = reinterpret_cast<ISteamClient017*>(G::Interface.Get(STEAMCLIENT_DLL, STEAMCLIENT_INTERFACE_VERSION_017));

	HSteamPipe hsNewPipe = Client->CreateSteamPipe();
	HSteamPipe hsNewUser = Client->ConnectToGlobalUser(hsNewPipe);

	Friends002 = reinterpret_cast<ISteamFriends002*>(Client->GetISteamFriends(hsNewUser, hsNewPipe, STEAMFRIENDS_INTERFACE_VERSION_002));
	Friends015 = reinterpret_cast<ISteamFriends015*>(Client->GetISteamFriends(hsNewUser, hsNewPipe, STEAMFRIENDS_INTERFACE_VERSION_015));
	Utils007 = reinterpret_cast<ISteamUtils007*>(Client->GetISteamUtils(hsNewUser, STEAMUTILS_INTERFACE_VERSION_007));
	SteamApps = reinterpret_cast<ISteamApps006*>(Client->GetISteamApps(hsNewUser, hsNewPipe, STEAMAPPS_INTERFACE_VERSION_006));
	UserStats = reinterpret_cast<ISteamUserStats011*>(Client->GetISteamUserStats(hsNewUser, hsNewPipe, STEAMUSERSTATS_INTERFACE_VERSION_011));
	User = reinterpret_cast<ISteamUser017*>(Client->GetISteamUser(hsNewUser, hsNewPipe, STEAMUSER_INTERFACE_VERSION_017));
}