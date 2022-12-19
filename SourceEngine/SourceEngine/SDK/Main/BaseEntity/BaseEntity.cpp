#include "BaseEntity.h"

#include "../../SDK.h"

bool C_BaseEntity::IsPlayer()
{
	return GetClientClass()->m_ClassID == CTFPlayer;
}

PlayerInfo_t steamfriendpi{};

bool C_BaseEntity::IsSteamFriend()
{
	if (I::Engine->GetPlayerInfo(this->entindex(), &steamfriendpi) && steamfriendpi.friendsID)
	{
		CSteamID steamID{ steamfriendpi.friendsID, 1, k_EUniversePublic, k_EAccountTypeIndividual };
		return I::Steam.Friends002->HasFriend(steamID, k_EFriendFlagImmediate);
	}

	return false;
}

C_BaseEntity* C_BaseEntity::GetGroundEntity()
{
	static auto pHandle = GetNetVar("CBasePlayer", "m_hGroundEntity");
	return reinterpret_cast<C_BaseEntity*>(I::EntityList->GetClientEntityFromHandle(reinterpret_cast<DWORD>(this) + pHandle));
}

bool C_BaseEntity::GetHitboxMinsAndMaxsAndMatrix(int nHitbox, Vec3& mins, Vec3& maxs, matrix3x4& matrix, Vec3* center)
{
	model_t* pModel = GetModel();
	if (!pModel)
	{
		return false;
	}

	studiohdr_t* pHdr = (studiohdr_t*)I::ModelInfo->GetStudioModel(pModel);
	if (!pHdr)
	{
		return false;
	}

	matrix3x4 BoneMatrix[128];
	if (!this->SetupBones(BoneMatrix, 128, 0x100, I::GlobalVars->curtime))
	{
		return false;
	}

	mstudiohitboxset_t* pSet = pHdr->pHitboxSet(this->m_nHitboxSet());
	if (!pSet)
	{
		return false;
	}

	mstudiobbox_t* pBox = pSet->hitbox(nHitbox);
	if (!pBox)
	{
		return false;
	}

	mins = pBox->bbmin;
	maxs = pBox->bbmax;
	memcpy(matrix, BoneMatrix[pBox->bone], sizeof(matrix3x4));

	if (center)
	{
		Math::VectorTransform(((pBox->bbmin + pBox->bbmax) * 0.5f), BoneMatrix[pBox->bone], *center);
	}

	return true;
}

bool C_BaseEntity::GetHitboxMinsAndMaxs(int nHitbox, Vec3& mins, Vec3& maxs, Vec3* center)
{
	model_t* pModel = GetModel();
	if (!pModel)
		return false;

	studiohdr_t* pHdr = (studiohdr_t*)I::ModelInfo->GetStudioModel(pModel);
	if (!pHdr)
		return false;

	matrix3x4 BoneMatrix[128];
	if (!this->SetupBones(BoneMatrix, 128, 0x100, I::GlobalVars->curtime))
		return false;

	mstudiohitboxset_t* pSet = pHdr->pHitboxSet(this->m_nHitboxSet());
	if (!pSet)
		return false;

	mstudiobbox_t* pBox = pSet->hitbox(nHitbox);
	if (!pBox)
		return false;

	mins = pBox->bbmin;
	maxs = pBox->bbmax;

	if (center)
		Math::VectorTransform(((pBox->bbmin + pBox->bbmax) * 0.5f), BoneMatrix[pBox->bone], *center);

	return true;
}

bool C_BaseEntity::IsInValidTeam()
{
	int Team = this->m_iTeamNum();
	return (Team == 2 || Team == 3);
}

C_BaseEntity* C_BaseEntity::FirstMoveChild() {
	return I::EntityList->GetClientEntity(*reinterpret_cast<int*>(this + 0x1B0) & 0xFFF);
}

C_BaseEntity* C_BaseEntity::NextMovePeer() {
	return I::EntityList->GetClientEntity(*reinterpret_cast<int*>(this + 0x1B4) & 0xFFF);
}

void C_BaseEntity::UpdateClientSideAnimation()
{
	void* renderable = (PVOID)(this + 0x4);
	typedef void(__thiscall* FN)(PVOID);
	return GetVFunc<FN>(renderable, 3)(renderable);
}

const Vec3& C_BaseEntity::GetRenderAngles()
{
	void* renderable = (PVOID)(this + 0x4);
	typedef const Vec3& (__thiscall* FN)(PVOID);
	return GetVFunc<FN>(renderable, 2)(renderable);
}

void C_BaseEntity::SetRenderAngles(const Vec3& v)
{
	Vec3* pRenderAngles = const_cast<Vec3*>(&this->GetRenderAngles());
	*pRenderAngles = v;
}

void C_BaseEntity::SetAbsOrigin(const Vec3& v)
{
	typedef void(__thiscall* FN)(C_BaseEntity*, const Vec3&);
	static DWORD dwFN = G::Pattern.Find("client.dll", "55 8B EC 56 57 8B F1 E8 ? ? ? ? 8B 7D 08 F3 0F 10 07");
	FN func = (FN)dwFN;
	func(this, v);
}

void C_BaseEntity::SetAbsAngles(const Vec3& v)
{
	/*typedef void(__thiscall *FN)(C_BaseEntity *, const Vec3 &);
	static DWORD dwFN = G::Pattern.FindInClient("55 8B EC 83 EC 60 56 57 8B F1 E8 ? ? ? ? 8B 7D 08 F3 0F 10 07 0F 2E 86 ? ? ? ? 9F F6 C4 44 7A 28 F3 0F 10 47 ?");
	FN func = (FN)dwFN;
	func(this, v);*/

	Vec3* pAbsAngles = const_cast<Vec3*>(&this->GetAbsAngles());
	*pAbsAngles = v;
}

const Vec3& C_BaseEntity::GetAbsOrigin()
{
	typedef Vec3& (__thiscall* FN)(PVOID);
	return GetVFunc<FN>(this, 9)(this);
}

//Recreated from "C_TFPlayer"
//Supposed to be used from local.
bool C_BaseEntity::IsPlayerOnSteamFriendList(C_BaseEntity* pEntity)
{
	PlayerInfo_t pi;
	if (I::Engine->GetPlayerInfo(pEntity->entindex(), &pi) && pi.friendsID)
	{
		CSteamID steamID{ pi.friendsID, 1, k_EUniversePublic, k_EAccountTypeIndividual };
		if (I::Steam.Friends002->HasFriend(steamID, k_EFriendFlagImmediate))
			return true;
	}

	return false;
}

const Vec3& C_BaseEntity::GetAbsAngles()
{
	typedef Vec3& (__thiscall* FN)(PVOID);
	return GetVFunc<FN>(this, 10)(this);
}

//C_UserCmd* C_BaseEntity::GetCurrentCommand()
//{
//	//DYNVAR_RETURN(C_UserCmd*, (this - 0x4), "DT_BasePlayer", "localdata", "m_hConstraintEntity");
//}

int C_BaseEntity::GetChokedTicks()
{
	float flDiff = I::GlobalVars->curtime - m_flSimulationTime();

	float flLatency = 0.0f;
	if (auto pNet = I::Engine->GetNetChannelInfo())
		flLatency = pNet->GetAvgLatency(FLOW_INCOMING);

	return TIME_TO_TICKS(std::max(0.0f, flDiff - flLatency));
}

const char* C_BaseEntity::GetModelName()
{
	return I::ModelInfo->GetModelName(this->GetModel());
}


bool C_BaseEntity::IsBaseCombatWeapon()
{
	typedef bool(__thiscall* FN)(PVOID);
	return GetVFunc<FN>(this, 137)(this);
}

bool C_BaseEntity::IsWearable()
{
	typedef bool(__thiscall* FN)(PVOID);
	return GetVFunc<FN>(this, 138)(this);
}

Vec3 C_BaseEntity::GetWorldSpaceCenter()
{
	Vec3 vMin, vMax;

	this->GetRenderBounds(vMin, vMax);
	Vec3 vWorldSpaceCenter = this->GetAbsOrigin();
	vWorldSpaceCenter.z += (vMin.z + vMax.z) / 2.0f;

	return vWorldSpaceCenter;
}

model_t* C_BaseEntity::GetModel()
{
	PVOID pRenderable = (PVOID)(this + 0x4);
	typedef model_t* (__thiscall* FN)(PVOID);
	return GetVFunc<FN>(pRenderable, 9)(pRenderable);
}

int C_BaseEntity::DrawModel(int flags)
{
	void* renderable = (PVOID)(this + 0x4);
	typedef int(__thiscall* FN)(PVOID, int);
	return GetVFunc<FN>(renderable, 10)(renderable, flags);
}

bool C_BaseEntity::SetupBones(matrix3x4* pBoneToWorldOut, int nMaxBones, int nBoneMask, float fCurrentTime)
{
	PVOID pRenderable = (PVOID)(this + 0x4);
	typedef bool(__thiscall* FN)(PVOID, matrix3x4*, int, int, float);
	return GetVFunc<FN>(pRenderable, 16)(pRenderable, pBoneToWorldOut, nMaxBones, nBoneMask, fCurrentTime);
}

ClientClass* C_BaseEntity::GetClientClass()
{
	PVOID pNetworkable = (PVOID)(this + 0x8);
	typedef ClientClass* (__thiscall* FN)(PVOID);
	return GetVFunc<FN>(pNetworkable, 2)(pNetworkable);
}

bool C_BaseEntity::IsDormant()
{
	PVOID pNetworkable = (PVOID)(this + 0x8);
	typedef bool(__thiscall* FN)(PVOID);
	return GetVFunc<FN>(pNetworkable, 8)(pNetworkable);
}

int C_BaseEntity::entindex()
{
	PVOID pNetworkable = (PVOID)(this + 0x8);
	typedef int(__thiscall* FN)(PVOID);
	return GetVFunc<FN>(pNetworkable, 9)(pNetworkable);
}

void C_BaseEntity::GetRenderBounds(Vec3& vMins, Vec3& vMaxs)
{
	PVOID pRenderable = (PVOID)(this + 0x4);
	typedef void(__thiscall* FN)(PVOID, Vec3&, Vec3&);
	GetVFunc<FN>(pRenderable, 20)(pRenderable, vMins, vMaxs);
}

matrix3x4& C_BaseEntity::GetRgflCoordinateFrame()
{
	PVOID pRenderable = (PVOID)(this + 0x4);
	typedef matrix3x4& (__thiscall* FN)(PVOID);
	return GetVFunc<FN>(pRenderable, 34)(pRenderable);
}

Vec3 C_BaseEntity::GetVelocity()
{
	typedef void(__thiscall* EstimateAbsVelocityFn)(C_BaseEntity*, Vec3&);
	static DWORD dwFn = G::Pattern.Find("client.dll", "E8 ? ? ? ? F3 0F 10 4D ? 8D 85 ? ? ? ? F3 0F 10 45 ? F3 0F 59 C9 56 F3 0F 59 C0 F3 0F 58 C8 0F 2F 0D ? ? ? ? 76 07") + 0x1;
	static DWORD dwEstimate = ((*(PDWORD)(dwFn)) + dwFn + 0x4);
	EstimateAbsVelocityFn vel = (EstimateAbsVelocityFn)dwEstimate;
	Vec3 v;
	vel(this, v);
	return v;
}

int C_BaseEntity::GetClassId()
{
	return this->GetClientClass()->m_ClassID;
}

int C_BaseEntity::GetMaxHealth()
{
	typedef int(__thiscall* FN)(PVOID);
	return GetVFunc<FN>(this, 107)(this);
}

bool C_BaseEntity::IsOnGround()
{
	return (this->m_fFlags() & FL_ONGROUND);
}

bool C_BaseEntity::IsInWater()
{
	return (this->m_fFlags() & FL_INWATER); //it's better to use IsSwimming method cuz this one doesn't work iirc.
}

Vec3 C_BaseEntity::GetHitboxPos(int nHitbox)
{
	model_t* pModel = GetModel();
	if (!pModel)
		return Vec3();

	studiohdr_t* pHdr = (studiohdr_t*)I::ModelInfo->GetStudioModel(pModel);
	if (!pHdr)
		return Vec3();

	matrix3x4 BoneMatrix[128];
	if (!this->SetupBones(BoneMatrix, 128, 0x100, I::GlobalVars->curtime))
		return Vec3();

	mstudiohitboxset_t* pSet = pHdr->pHitboxSet(this->m_nHitboxSet());
	if (!pSet)
		return Vec3();

	mstudiobbox_t* pBox = pSet->hitbox(nHitbox);
	if (!pBox)
		return Vec3();

	Vec3 vPos = (pBox->bbmin + pBox->bbmax) * 0.5f;
	Vec3 vOut = Vec3();

	Math::VectorTransform(vPos, BoneMatrix[pBox->bone], vOut);

	return vOut;
}

int C_BaseEntity::GetNumOfHitboxes()
{
	model_t* pModel = GetModel();
	if (!pModel)
	{
		return 0;
	}

	studiohdr_t* pHdr = (studiohdr_t*)I::ModelInfo->GetStudioModel(pModel);
	if (!pHdr)
	{
		return 0;
	}

	mstudiohitboxset_t* pSet = pHdr->pHitboxSet(this->m_nHitboxSet());
	if (!pSet)
	{
		return 0;
	}

	return pSet->numhitboxes;
}

Vec3 C_BaseEntity::GetBonePos(int nBone)
{
	matrix3x4 matrix[128];

	if (this->SetupBones(matrix, 128, 0x100, GetTickCount64()))
	{
		return Vec3(matrix[nBone][0][3], matrix[nBone][1][3], matrix[nBone][2][3]);
	}

	return Vec3(0.0f, 0.0f, 0.0f);
}

C_BaseCombatWeapon* C_BaseEntity::GetActiveWeapon()
{
	auto hActiveWeapon = this->m_hActiveWeapon();
	return reinterpret_cast<C_BaseCombatWeapon*>(I::EntityList->GetClientEntityFromHandle(hActiveWeapon));
}


bool C_BaseEntity::IsAlive()
{
	return !(this->deadflag());
}

bool C_BaseEntity::IsDucking()
{
	return (this->m_fFlags() & FL_DUCKING);
}