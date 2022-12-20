#pragma once

#include "../SDK/SDK.h"

namespace CFG
{
	struct ConfigVarInitializer
	{
		const char* m_szName{ nullptr };
		void* m_pValuePointer{ nullptr };
		size_t m_nTypeHash{ 0 };
	};

	inline std::vector<ConfigVarInitializer> Vars{};

	void Save(const char* path);

	void Load(const char* path);
}

#define CFGVAR(var, val) namespace V { inline auto var{ val }; }\
namespace ConfigInitializers\
{\
	inline auto var##_initializer = []()\
	{\
		CFG::Vars.push_back(CFG::ConfigVarInitializer{ #var, &V::var, typeid(V::var).hash_code() });\
		return true;\
	}();\
}

#define CFGVAR_NOSAVE(var, val) namespace V { inline auto var { val }; }

CFGVAR(Movement_Bunnyhop, true);
CFGVAR(Movement_NoPush, true);

CFGVAR(Menu_Text, Color_t({ 220, 220, 220, 255 }));
CFGVAR(Menu_ListWidth, int(200));
CFGVAR(Menu_ListBarH, int(30));
CFGVAR(Menu_ListBG, Color_t({ 40, 40, 40, 255 }));
CFGVAR(Menu_ListBar, Color_t({ 30, 30, 30, 255 }));
CFGVAR(Menu_ListOutline, Color_t({ 100, 100, 100, 255 }));
CFGVAR(Menu_GroupH, int(20));
CFGVAR(Menu_GroupBG, Color_t({ 35, 35, 35, 255 }));
CFGVAR(Menu_GroupHover, Color_t({ 60, 60, 60, 255 }));
CFGVAR(Menu_ItemBG, Color_t({ 80, 80, 80, 255 }));
CFGVAR(Menu_ItemHover, Color_t({ 225, 177, 44, 255 }));

CFGVAR(ESP_Enabled, true);
CFGVAR(ESP_Outline, true);
CFGVAR(ESP_EnemyOnly, true);
CFGVAR(ESP_Box, true);
CFGVAR(ESP_Name, true);
CFGVAR(ESP_Health, true);
CFGVAR(ESP_Armour, true);
CFGVAR(ESP_Distance, true);
CFGVAR(ESP_HealthLow, Color_t({ 255, 83, 83, 255 }));
CFGVAR(ESP_HealthHigh, Color_t({ 83, 255, 91, 255 }));
CFGVAR(ESP_ArmourLow, Color_t({ 132, 83, 255, 255 }));
CFGVAR(ESP_ArmourHigh, Color_t({ 83, 241, 255, 255 }));

CFGVAR(Chams_Enabled, true);
CFGVAR(Chams_EnemyOnly, true);
CFGVAR(Chams_OccludedMaterial, 1); // None, Shaded, Flat, Shiny
CFGVAR(Chams_UnoccludedMaterial, 0); // None, Shaded, Flat, Shiny
CFGVAR(Chams_OccludedUseCustomColor, false);
CFGVAR(Chams_UnoccludedUseCustomColor, false);
CFGVAR(Chams_OccludedColor, Color_t({ 255,255,255,255 }));
CFGVAR(Chams_UnoccludedColor, Color_t({ 255,255,255,255 }));

CFGVAR(Colors_OutlineColor, Color_t({ 0, 0, 0, 255 }));
CFGVAR(Colors_CondColor, Color_t({ 254, 202, 87, 255 }));
CFGVAR(Colors_TargetColor, Color_t({ 153, 128, 250, 255 }));
CFGVAR(Colors_InvulnColor, Color_t({ 59, 59, 152, 255 }));
CFGVAR(Colors_CloakColor, Color_t({ 165, 177, 194, 255 }));
CFGVAR(Colors_FriendColor, Color_t({ 152, 255, 152, 255 }));
CFGVAR(Colors_OverhealColor, Color_t({ 84, 160, 255, 255 }));
CFGVAR(Colors_EnemyColor, Color_t({ 255, 176, 74, 255 }));
CFGVAR(Colors_TeamColor, Color_t({ 74, 255, 95, 255 }));

CFGVAR(Aimbot_Enabled, true);
CFGVAR(Aimbot_AimKey, VK_XBUTTON1);
CFGVAR(Aimbot_Hitbox, 0); // Auto - Head - Body
CFGVAR(Aimbot_FoV, 60);

CFGVAR(Misc_FoV, 120);
CFGVAR(Misc_Show_Aimbot_FoV, true);
CFGVAR(Misc_Remove_Visual_Punch, true);

CFGVAR(Exploits_SequenceFreezing_Key, 82);
CFGVAR(Exploits_SequenceFreezing_Value, 900);
CFGVAR(Exploits_Airstuck_Key, 72);
CFGVAR(Exploits_Speedhack_Key, 70);