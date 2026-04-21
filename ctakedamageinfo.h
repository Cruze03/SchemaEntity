#pragma once
#include <platform.h>
#include "ehandle.h"
#include "globaltypes.h"

class CBaseEntity;
class CCSPlayerPawn;

struct AttackerInfo_t
{
	bool m_bNeedInit;
	bool m_bIsPawn;
	bool m_bIsWorld;
	CHandle<CCSPlayerPawn> m_hAttackerPawn;
	int32_t m_nAttackerPlayerSlot;
	int m_iTeamChecked;
	int m_nTeam;
};
static_assert(sizeof(AttackerInfo_t) == 20);

class CGameTrace;

class CTakeDamageInfo
{
public:
	DECLARE_SCHEMA_CLASS(CTakeDamageInfo)

	SCHEMA_FIELD(Vector, m_vecDamageForce);
	SCHEMA_FIELD(Vector, m_vecDamagePosition);
	SCHEMA_FIELD(Vector, m_vecReportedPosition);
	SCHEMA_FIELD(Vector, m_vecDamageDirection);
	SCHEMA_FIELD(CBaseHandle, m_hInflictor);
	SCHEMA_FIELD(CBaseHandle, m_hAttacker);
	SCHEMA_FIELD(CBaseHandle, m_hAbility);
	SCHEMA_FIELD(float, m_flDamage);
	SCHEMA_FIELD(float, m_flTotalledDamage);
	SCHEMA_FIELD(int32_t, m_bitsDamageType);
	SCHEMA_FIELD(int32_t, m_iDamageCustom);
	SCHEMA_FIELD(int8_t, m_iAmmoType);
	SCHEMA_FIELD(float, m_flOriginalDamage);
	SCHEMA_FIELD(bool, m_bShouldBleed);
	SCHEMA_FIELD(bool, m_bShouldSpark);

	// SCHEMA_FIELD(float, m_flDamageAbsorbed);
	SCHEMA_FIELD(TakeDamageFlags_t, m_nDamageFlags);
	SCHEMA_FIELD(HitGroup_t, m_iHitGroupId);
	SCHEMA_FIELD(int32_t, m_nNumObjectsPenetrated);
	SCHEMA_FIELD(float, m_flFriendlyFireDamageReductionRatio);
	SCHEMA_FIELD(bool, m_bStoppedBullet);

	SCHEMA_FIELD(AttackerInfo_t, m_AttackerInfo);
	// CUtlLeanVector<int> m_DestructibleHitGroupRequests
	SCHEMA_FIELD(bool, m_bInTakeDamageFlow);
};

struct CTakeDamageResult
{
public:
	CTakeDamageInfo *m_pOriginatingInfo;
	CUtlLeanVector<int> m_DestructibleHitGroupRequests; // CUtlLeanVector<DestructiblePartDamageRequest_t>
	int32_t m_nHealthLost;
	int32_t m_nHealthBefore;
	float m_flDamageDealt;
	float m_flPreModifiedDamage;
	int32_t m_nTotalledHealthLost;
	float m_flTotalledDamageDealt;
	float m_flTotalledPreModifiedDamage;
	float m_flNewDamageAccumulatorValue;
	TakeDamageFlags_t m_nDamageFlags;
	bool m_bWasDamageSuppressed;
	bool m_bSuppressFlinch;
	HitGroup_t m_nOverrideFlinchHitGroup;

private:
	[[maybe_unused]] uint8_t m_nUnknown0[0x8];

public:
	void CopyFrom(CTakeDamageInfo *pInfo)
	{
		m_pOriginatingInfo = pInfo;
		m_nHealthLost = static_cast<int32_t>(pInfo->m_flDamage);
		m_nHealthBefore = 0;
		m_flDamageDealt = pInfo->m_flDamage;
		m_flPreModifiedDamage = pInfo->m_flDamage;
		m_nTotalledHealthLost = static_cast<int32_t>(pInfo->m_flDamage);
		m_flTotalledDamageDealt = pInfo->m_flDamage;
		m_bWasDamageSuppressed = false;
	}

	CTakeDamageResult() = delete;

	CTakeDamageResult(float damage) : m_pOriginatingInfo(nullptr),
									  m_nHealthLost(static_cast<int32_t>(damage)),
									  m_nHealthBefore(0),
									  m_flDamageDealt(damage),
									  m_flPreModifiedDamage(damage),
									  m_nTotalledHealthLost(static_cast<int32_t>(damage)),
									  m_flTotalledDamageDealt(damage),
									  m_bWasDamageSuppressed(false)
	{
	}
};
static_assert(sizeof(CTakeDamageResult) == 80);