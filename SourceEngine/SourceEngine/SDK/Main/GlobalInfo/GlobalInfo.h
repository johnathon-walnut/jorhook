#pragma once
#pragma once
#include "../BaseEntity/BaseEntity.h"

struct GlobalInfo_t
{
	//vars
	int nCurrentTargetIdx = 0;
	bool bWeaponCanHeadShot = false;
	bool bWeaponCanShoot = false;
	float fChargeTime = 0.0f;
	Vec3 vecUCMDAngles = Vec3();

	//temporary place for some features I guess
	bool bNoInterpolation = true;
	Vec3 vecPredictedPos = Vec3();

	Vec3 vecPunchAngles = Vec3();

	bool bSequenceFreezing = false;
	Vec3 vecLastPos = Vec3();

	//Fuck
	bool m_bDrawMenu = false;
	int m_nFocusOverlay = 0;

	VMatrix WorldToProjection = {};

	int nTicks = 0;
};

inline GlobalInfo_t gGlobalInfo;