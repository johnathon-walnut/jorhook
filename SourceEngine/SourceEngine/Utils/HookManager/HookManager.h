#pragma once

#include "../../SDK/SDK.h"
#include "../Minhook/include/MinHook.h"

using HookInitFN = void(__cdecl*)();

struct CHook
{
	void* m_pOriginalFN;
	void* m_pInitFunction;

	inline void CreateHook(void* pSource, void* pDestination)
	{
		MH_CreateHook(pSource, pDestination, &m_pOriginalFN);
	}

	template <typename FN> inline FN Original()
	{
		return reinterpret_cast<FN>(m_pOriginalFN);
	}

	CHook(void* pInitFunction);
};

class CHookManager
{
public:
	void Initialize();
	void Release();

	std::vector<CHook*>& GetHooks();

	std::vector<CHook*> m_Hooks;
};

MAKE_FEATURE(CHookManager, HookManager);