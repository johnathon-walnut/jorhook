#pragma once
#include "../BaseEntity/BaseEntity.h"

class C_BaseObject : public C_BaseEntity
{
public:
	NETVAR(m_iHealth, int, "CBaseObject", "m_iHealth");
	NETVAR(m_iMaxHealth, int, "CBaseObject", "m_iMaxHealth");
	NETVAR(m_bHasSapper, bool, "CBaseObject", "m_bHasSapper");
	NETVAR(m_iObjectType, int, "CBaseObject", "m_iObjectType");
	NETVAR(m_bBuilding, bool, "CBaseObject", "m_bBuilding");
	NETVAR(m_bPlacing, bool, "CBaseObject", "m_bPlacing");
	NETVAR(m_bCarried, bool, "CBaseObject", "m_bCarried");
	NETVAR(m_bCarryDeploy, bool, "CBaseObject", "m_bCarryDeploy");
	NETVAR(m_flPercentageConstructed, float, "CBaseObject", "m_flPercentageConstructed");
	NETVAR(m_fObjectFlags, int, "CBaseObject", "m_fObjectFlags");
	NETVAR(m_hBuiltOnEntity, int, "CBaseObject", "m_hBuiltOnEntity");
	NETVAR(m_bDisabled, bool, "CBaseObject", "m_bDisabled");
	NETVAR(m_hBuilder, int, "CBaseObject", "m_hBuilder");
	NETVAR(m_vecBuildMaxs, Vec3, "CBaseObject", "m_vecBuildMaxs");
	NETVAR(m_vecBuildMins, Vec3, "CBaseObject", "m_vecBuildMins");
	NETVAR(m_iDesiredBuildRotations, int, "CBaseObject", "m_iDesiredBuildRotations");
	NETVAR(m_bServerOverridePlacement, bool, "CBaseObject", "m_bServerOverridePlacement");
	NETVAR(m_iUpgradeLevel, int, "CBaseObject", "m_iUpgradeLevel");
	NETVAR(m_iUpgradeMetal, int, "CBaseObject", "m_iUpgradeMetal");
	NETVAR(m_iUpgradeMetalRequired, int, "CBaseObject", "m_iUpgradeMetalRequired");
	NETVAR(m_iHighestUpgradeLevel, int, "CBaseObject", "m_iHighestUpgradeLevel");
	NETVAR(m_iObjectMode, int, "CBaseObject", "m_iObjectMode");
	NETVAR(m_bWasMapPlaced, bool, "CBaseObject", "m_bWasMapPlaced");
	NETVAR(m_bEnemyUsing, bool, "CBaseObject", "m_bEnemyUsing");
};