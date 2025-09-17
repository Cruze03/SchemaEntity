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
private:
	[[maybe_unused]] uint8_t __pad0000[0x8];

public:
	Vector m_vecDamageForce;	  // 0x8  |  8
	Vector m_vecDamagePosition;	  // 0x14 | 20
	Vector m_vecReportedPosition; // 0x20 | 32
	Vector m_vecDamageDirection;  // 0x2c | 44
	CBaseHandle m_hInflictor;	  // 0x38 | 56
	CBaseHandle m_hAttacker;	  // 0x3c | 60
	CBaseHandle m_hAbility;		  // 0x40 | 64
	float m_flDamage;			  // 0x44 | 68
	float m_flTotalledDamage;	  // 0x48 | 72
	int32_t m_bitsDamageType;	  // 0x4c | 76
	int32_t m_iDamageCustom;	  // 0x50 | 80
	int8_t m_iAmmoType;			  // 0x54 | 84

private:
	[[maybe_unused]] uint8_t m_nUnknown0[0xb]; // 0x55 | 85

public:
	float m_flOriginalDamage; // 0x60 | 96
	bool m_bShouldBleed;	  // 0x64 | 100
	bool m_bShouldSpark;	  // 0x65 | 101

private:
	[[maybe_unused]] uint8_t m_nUnknown1[0x2]; // 0x66

public:
	CGameTrace* m_pTrace;			  // 0x68 | 104
	TakeDamageFlags_t m_nDamageFlags; // 0x70 | 112

private:
	[[maybe_unused]] uint8_t m_sDamageSourceName[0x8]; // 0x78 | 120

public:
	HitGroup_t m_iHitGroupId;					// 0x80 | 128
	int32_t m_nNumObjectsPenetrated;			// 0x84 | 132
	float m_flFriendlyFireDamageReductionRatio; // 0x88 | 136
private:
	uint8_t m_nUnknown2[0x5C]; // 0x9c | 140
public:
	void* m_hScriptInstance;	   // 0xe8 | 232
	AttackerInfo_t m_AttackerInfo; // 0xf0 | 240
	bool m_bInTakeDamageFlow;	   // 0x104 | 260

private:
	[[maybe_unused]] int32_t m_nUnknown3; // 0x108 | 264
};
static_assert(sizeof(CTakeDamageInfo) == 272);

struct CTakeDamageInfoContainer
{
	CTakeDamageInfo* pInfo;
};