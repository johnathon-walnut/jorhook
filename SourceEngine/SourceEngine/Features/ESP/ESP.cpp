#include "ESP.h"

void CESP::Run()
{
	if (!V::ESP_Enabled)
	{
		return;
	}

	if (!I::Engine->IsInGame() || 
		!I::Engine->IsConnected() ||
		I::Engine->Con_IsVisible() ||
		I::EngineVGui->IsGameUIVisible())
	{
		return;
	}

	const auto& pLocal = G::EntityCache.pLocal;

	if (!pLocal)
	{
		return;
	}

	Vec3 vTrans[8]{};

	const Vec3 vLocalPos = pLocal->m_vecOrigin();

	int x{}, y{}, w{}, h{};

	PlayerInfo_t pi{};

	const int nLocalTeamnum = pLocal->m_iTeamNum();

	for (const auto& pEntity : V::ESP_EnemyOnly ? G::EntityCache.GetGroup(GroupType_t::PLAYERS_ENEMIES) : G::EntityCache.GetGroup(GroupType_t::PLAYERS_ALL))
	{
		if (pEntity->deadflag() || 
			pEntity->IsDormant() || 
			pEntity->m_iTeamNum() == nLocalTeamnum)
		{
			continue;
		}

		if (!I::Engine->GetPlayerInfo(pEntity->entindex(), &pi))
		{
			continue;
		}

		if (!GetDrawBounds(pEntity, vTrans, x, y, w, h))
		{
			continue;
		}

		const int nClass = pEntity->m_iClass();
		const int nHealth = pEntity->m_iHealth();
		const int nMaxHealth = pEntity->GetMaxHealth();
		const int nArmour = pEntity->m_ArmorValue();
		const int nMaxArmour = GetMaxArmorValue(nClass);

		const Color_t& entityColour = GetEntityColor(pEntity, nLocalTeamnum);

		if (V::ESP_Box)
		{
			G::Draw.OutlinedRect(x, y, w, h, entityColour);
			if (V::ESP_Outline)
			{
				G::Draw.OutlinedRect(x - 1, y - 1, w + 2, h + 2, V::Colors_OutlineColor);
				G::Draw.OutlinedRect(x + 1, y + 1, w - 2, h - 2, V::Colors_OutlineColor);
			}
		}

		if (V::ESP_Name)
		{
			const auto& pName = UTF8toWide(pi.name);
			G::Draw.StringCenterW(FONT_ESP, x + (w / 2), y - 14, entityColour, pName.c_str());
		}

		int hbx = x;
		int hby = y;

		if (V::ESP_Health)
		{
			float flHealth = nHealth > nMaxHealth ? nMaxHealth : nHealth;
			float flRatio = (static_cast<float>(nHealth) / static_cast<float>(nMaxHealth));
			const Color_t healthColour = G::Draw.LerpColor(V::ESP_HealthLow, V::ESP_HealthHigh, Math::RemapValClamped(nHealth, 0, nMaxHealth, 0.0f, 1.0f));
			G::Draw.Rect(hbx - 5, -1 + hby + h - (h * flRatio), 2, h * flRatio + 1, healthColour);
			if (V::ESP_Outline)
			{
				G::Draw.OutlinedRect(hbx - 6, -2 + hby + h - (h * flRatio) + 1, 4, 2 + h * flRatio, V::Colors_OutlineColor);
			}
			hbx -= 5;
		}

		if (V::ESP_Armour)
		{
			float flHealth = nArmour > nMaxArmour ? nMaxArmour : nArmour;
			float flRatio = (static_cast<float>(nArmour) / static_cast<float>(nMaxArmour));
			const Color_t healthColour = G::Draw.LerpColor(V::ESP_ArmourLow, V::ESP_ArmourHigh, Math::RemapValClamped(nArmour, 0, nMaxArmour, 0.0f, 1.0f));
			G::Draw.Rect(hbx - 5, -1 + hby + h - (h * flRatio), 2, h * flRatio + 1, healthColour);
			if (V::ESP_Outline)
			{
				G::Draw.OutlinedRect(hbx - 6, -2 + hby + h - (h * flRatio) + 1, 4, 2 + h * flRatio, V::Colors_OutlineColor);
			}
		}

		if (V::ESP_Distance)
		{
			const float flDistance = pEntity->m_vecOrigin().DistTo(vLocalPos);

			G::Draw.StringCenter(FONT_ESP_NAME, x + (w / 2), y + h + 2, { 255,255,255,255 }, "[%dm]", static_cast<int>(flDistance * 0.01905f));
		}


		/*
		CFGVAR(ESP_Enabled, true);
		CFGVAR(ESP_Outline, true);
		CFGVAR(ESP_Box, true);
		CFGVAR(ESP_Name, true);
		CFGVAR(ESP_Health, true);
		CFGVAR(ESP_Armour, true);
		CFGVAR(ESP_Conditions, true);
		CFGVAR(ESP_Distance, true);
		CFGVAR(ESP_HealthLow, Color_t({ 255, 83, 83, 255 }));
CFGVAR(ESP_HealthHigh, Color_t({ 83, 255, 91, 255 }));
CFGVAR(ESP_ArmourLow, Color_t({ 132, 83, 255, 255 }));
CFGVAR(ESP_ArmourHigh, Color_t({ 83, 241, 255, 255 }));*/
	}
}

bool CESP::GetDrawBounds(C_BaseEntity* pEntity, Vec3* vTrans, int& x, int& y, int& w, int& h)
{
	auto& vMins = pEntity->m_vecMins();
	auto& vMaxs = pEntity->m_vecMaxs();

	const matrix3x4& transform = pEntity->GetRgflCoordinateFrame();

	const Vec3 vPoints[] =
	{
		{vMins.x, vMins.y, vMins.z},
		{vMins.x, vMaxs.y, vMins.z},
		{vMaxs.x, vMaxs.y, vMins.z},
		{vMaxs.x, vMins.y, vMins.z},
		{vMaxs.x, vMaxs.y, vMaxs.z},
		{vMins.x, vMaxs.y, vMaxs.z},
		{vMins.x, vMins.y, vMaxs.z},
		{vMaxs.x, vMins.y, vMaxs.z}
	};

	for (int n = 0; n < 8; n++)
	{
		Math::VectorTransform(vPoints[n], transform, vTrans[n]);
	}

	Vec2 flb, brt, blb, frt, frb, brb, blt, flt;

	if (W2S(vTrans[3], flb) && W2S(vTrans[5], brt) &&
		W2S(vTrans[0], blb) && W2S(vTrans[4], frt) &&
		W2S(vTrans[2], frb) && W2S(vTrans[1], brb) &&
		W2S(vTrans[6], blt) && W2S(vTrans[7], flt))
	{
		const Vec2 arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };


		float left = flb.x;
		float top = flb.y;
		float righ = flb.x;
		float bottom = flb.y;

		for (int n = 1; n < 8; n++)
		{
			if (left > arr[n].x)
			{
				left = arr[n].x;
			}

			if (top < arr[n].y)
			{
				top = arr[n].y;
			}

			if (righ < arr[n].x)
			{
				righ = arr[n].x;
			}

			if (bottom > arr[n].y)
			{
				bottom = arr[n].y;
			}
		}

		float x_ = left;
		const float y_ = bottom;
		float w_ = righ - left;
		const float h_ = top - bottom;

		x_ += (righ - left) / 8.0f;
		w_ -= (righ - left) / 8.0f * 2.0f;

		x = static_cast<int>(x_);
		y = static_cast<int>(y_);
		w = static_cast<int>(w_);
		h = static_cast<int>(h_);

		return !(x > G::ScreenSize.w || x + w < 0 || y > G::ScreenSize.h || y + h < 0);
	}

	return false;
}


int CESP::GetMaxArmorValue(int nClass)
{
	switch (nClass)
	{
		default:
		{
			return 0;
		}
		case CLASS_SCOUT:
		case CLASS_SNIPER:
		{
			return 25;
		}
		case CLASS_SOLDIER:
		case CLASS_PYRO:
		{
			return 150;
		}
		case CLASS_DEMO:
		case CLASS_MEDIC:
		{
			return 100;
		}
		case CLASS_HEAVY:
		{
			return 225;
		}
		case CLASS_ENGINEER:
		case CLASS_SPY:
		{
			return 50;
		}
	}
}



const Color_t CESP::GetEntityColor(C_BaseEntity* pEntity, int nLocalTeam)
{
	Color_t* outColour = &V::Colors_OutlineColor;

	if (pEntity->m_iTeamNum() == nLocalTeam)
	{
		outColour = &V::Colors_TeamColor;
	}
	else
	{
		outColour = &V::Colors_EnemyColor;
	}

	if (G::EntityCache.m_bFriends[pEntity->entindex()])
	{
		outColour = &V::Colors_FriendColor;
	}

	if (pEntity->entindex() == gGlobalInfo.nCurrentTargetIdx)
	{
		outColour = &V::Colors_TargetColor;
	}

	return *outColour;
}

const std::wstring CESP::UTF8toWide(const std::string& str)
{
	int count = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
	std::wstring wstr(count, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &wstr[0], count);
	return wstr;
}
