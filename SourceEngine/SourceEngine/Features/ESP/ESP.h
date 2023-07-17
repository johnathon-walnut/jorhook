#pragma once

#include "../Vars.h"

class CESP
{
public:
	void DrawPlayer(C_BaseEntity* pEntity, PlayerInfo_t& pi, const Vec3& vLocalPos, int x, int y, int w, int h, int nLocalTeamnum);
	void Run();
	bool GetDrawBounds(C_BaseEntity* pEntity, Vec3* vTrans, int& x, int& y, int& w, int& h);
	int GetMaxArmorValue(int nClass);
	const Color_t GetEntityColor(C_BaseEntity* pEntity, int nLocalTeam);
	const std::wstring UTF8toWide(const std::string& str);
	const std::wstring GetGameClassName(int nClass);
};

MAKE_FEATURE(CESP, ESP);