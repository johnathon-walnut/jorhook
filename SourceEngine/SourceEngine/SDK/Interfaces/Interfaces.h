#pragma once

#include "EngineClient/EngineClient.h"
#include "BaseClientDLL/BaseClientDLL.h"
#include "ClientDLLSharedAppSystems/ClientDLLSharedAppSystems.h"
#include "ClientModeShared/ClientModeShared.h"
#include "GlobalVarsBase/GlobalVarsBase.h"
#include "ClientEntityList/ClientEntityList.h"
#include "ModelInfo/ModelInfo.h"
#include "EngineTrace/EngineTrace.h"
#include "GameMovement/GameMovement.h"
#include "MoveHelper/MoveHelper.h"
#include "ConVar/ConVar.h"
#include "Prediction/Prediction.h"
#include "Panel/Panel.h"
#include "Surface/Surface.h"
#include "RenderView/RenderView.h"
#include "EngineVGui/EngineVGui.h"
#include "NetChannel/NetChannel.h"
#include "GameEvent/GameEvent.h"
#include "DebugOverlay/DebugOverlay.h"
#include "Steam/Steamworks.h"
#include "Steam/SteamTypes.h"
#include "MaterialSystem/MaterialSystem.h"

class C_SteamInterfaces
{
public:
	ISteamFriends002* Friends002 = nullptr;
	ISteamFriends015* Friends015 = nullptr;
	ISteamApps006* SteamApps = nullptr;
	ISteamUserStats011* UserStats = nullptr;
	ISteamClient017* Client = nullptr;
	ISteamUser017* User = nullptr;
	ISteamUtils007* Utils007 = nullptr;

	void Initialize();
};

namespace I
{
	inline C_BaseClientDLL* Client = nullptr;
	inline C_ClientDLLSharedAppSystems* ClientShared = nullptr;
	inline C_ClientModeShared* ClientMode = nullptr;
	inline C_EngineClient* Engine = nullptr;
	inline C_Panel* Panel = nullptr;
	inline C_Surface* Surface = nullptr;
	inline ISurface* MatSystemSurface = nullptr;
	inline C_ClientEntityList* EntityList = nullptr;
	inline C_ModelInfoClient* ModelInfo = nullptr;
	inline C_EngineTrace* EngineTrace = nullptr;
	inline C_Prediction* Prediction = nullptr;
	inline C_GameMovement* GameMovement = nullptr;
	inline C_MoveHelper* MoveHelper = nullptr;
	inline ICvar* CVars = nullptr; //hello, I am ICvar and I do not associate with C_ niggas
	inline C_GlobalVarsBase* GlobalVars = nullptr;
	inline C_EngineVGui* EngineVGui = nullptr;
	inline int32_t* RandomSeed = nullptr; //What about me?!?!
	inline void* DemoPlayer = nullptr; //hHaha we're getting STRONG!!1
	inline C_GameEventManager* GameEvent = nullptr; //Normally this would be another traitor but I added C_
	inline C_RenderView* RenderView = nullptr;
	inline IDebugOverlay* DebugOverlay = nullptr; //Back at it MF
	inline IMaterialSystem* MaterialSystem = nullptr;
	inline CModelRender* ModelRender = nullptr;

	void Initialize();

	inline C_SteamInterfaces Steam;
};