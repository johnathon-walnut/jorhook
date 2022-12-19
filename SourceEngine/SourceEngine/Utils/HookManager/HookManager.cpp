#include "HookManager.h"

CHook::CHook(void* pInitFunction)
{
	m_pInitFunction = pInitFunction;

	F::HookManager.m_Hooks.push_back(this);
}

void CHookManager::Initialize()
{
	assert(MH_Initialize() == MH_OK);
	
	for (const auto& Hook : m_Hooks)
	{
		reinterpret_cast<HookInitFN>(Hook->m_pInitFunction)();
	}

	assert(MH_EnableHook(MH_ALL_HOOKS) == MH_OK);
}

void CHookManager::Release()
{
	assert(MH_Uninitialize() == MH_OK);
}
