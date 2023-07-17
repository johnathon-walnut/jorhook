#pragma once

#include "../../SDK/SDK.h"
#include "../Minhook/include/MinHook.h"

using HookInitFN = void(__cdecl*)();

struct CHook
{
	void* m_pOriginalFN;
	void* m_pInitFunction;
	std::string m_sHookName;

	inline void CreateHook(void* pSource, void* pDestination)
	{
		MH_CreateHook(pSource, pDestination, &m_pOriginalFN);
	}

	template <typename FN> inline FN Original()
	{
		return reinterpret_cast<FN>(m_pOriginalFN);
	}

	CHook(std::string sHookName, void* pInitFunction);
};

class CHookManager
{
public:
	void Initialize();
	void Release();

	std::unordered_map<std::string, CHook*>& GetMapHooks()
	{
		static std::unordered_map<std::string, CHook*> mapHooks;
		return mapHooks;
	}
};

MAKE_FEATURE(CHookManager, HookManager);