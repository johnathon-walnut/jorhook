#include "VisCheck.h"

#include "../../Includes/Includes.h"

bool C_TraceFilterHitscan::ShouldHitEntity(void* pEntityHandle, int nContentsMask)
{
	C_BaseEntity* pEntity = reinterpret_cast<C_BaseEntity*>(pEntityHandle);

	if (pEntity)
	{
		switch (pEntity->GetClassId())
		{
			case CFuncAreaPortalWindow:
			case CFuncRespawnRoomVisualizer:
			case CSniperDot:
			{
				return false;
			}
		}
	}	

	return (pEntityHandle != pSkip);
}

TraceType_t C_TraceFilterHitscan::GetTraceType() const
{
	return TraceType_t::TRACE_EVERYTHING;
}

bool C_TraceFilterWorldAndPropsOnly::ShouldHitEntity(void *pEntityHandle, int nContentsMask)
{
	C_BaseEntity *pEntity = reinterpret_cast<C_BaseEntity *>(pEntityHandle);

	if (pEntity->GetClientClass()->m_ClassID == CTFPlayer)
		return false;

	return !(pEntityHandle == pSkip);
}

TraceType_t C_TraceFilterWorldAndPropsOnly::GetTraceType() const
{
	return TraceType_t::TRACE_EVERYTHING;
}

bool C_TraceFilterWorldAndPropsOnlyOther::ShouldHitEntity(void *pEntityHandle, int nContentsMask)
{
	C_BaseEntity *pEntity = reinterpret_cast<C_BaseEntity *>(pEntityHandle);

	if (pEntity->GetClientClass()->m_ClassID == CTFPlayer)
		return false;

	return !(pEntityHandle == pSkip);
}

TraceType_t C_TraceFilterWorldAndPropsOnlyOther::GetTraceType() const
{
	return TraceType_t::TRACE_EVERYTHING;
}

//=======================================================================================================

bool CVisCheck::Pos(C_BaseEntity* pSkip, C_BaseEntity* pEntity, const Vec3& from, const Vec3& to)
{
	Ray_t ray;
	ray.Init(from, to);

	const uint32_t mask = (MASK_SHOT | CONTENTS_GRATE);

	C_TraceFilterHitscan filter;
	filter.pSkip = pSkip;

	C_GameTrace trace;
	I::EngineTrace->TraceRay(ray, mask, &filter, &trace);

	return ((trace.entity && trace.entity == pEntity) || trace.flFraction >= 0.99f);
}

bool CVisCheck::PosHitboxId(C_BaseEntity* pSkip, C_BaseEntity* pEntity, const Vec3& from, const Vec3& to, int nHitbox)
{
	Ray_t ray;
	ray.Init(from, to);

	const uint32_t mask = (MASK_SHOT | CONTENTS_GRATE);

	C_TraceFilterHitscan filter;
	filter.pSkip = pSkip;

	C_GameTrace trace;
	I::EngineTrace->TraceRay(ray, mask, &filter, &trace);

	return (trace.entity && trace.entity == pEntity && trace.hitbox == nHitbox);
}

bool CVisCheck::PosHitboxIdOut(C_BaseEntity* pSkip, C_BaseEntity* pEntity, const Vec3& from, const Vec3& to, int& nHitboxOut)
{
	Ray_t ray;
	ray.Init(from, to);

	const uint32_t mask = (MASK_SHOT | CONTENTS_GRATE);

	C_TraceFilterHitscan filter;
	filter.pSkip = pSkip;

	C_GameTrace trace;
	I::EngineTrace->TraceRay(ray, mask, &filter, &trace);

	if (trace.entity && trace.entity == pEntity)
	{
		nHitboxOut = trace.hitbox;
		return true;
	}

	return false;
}
