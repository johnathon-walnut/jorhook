#include "HookManager.h"

CHook::CHook(void* pInitFunction)
{
	m_pInitFunction = pInitFunction;

	F::HookManager.GetHooks().push_back(this);
}

void CHookManager::Initialize()
{
	assert(MH_Initialize() == MH_OK);
	
	for (const auto& Hook : GetHooks())
	{
		reinterpret_cast<HookInitFN>(Hook->m_pInitFunction)();
		I::CVars->ConsolePrintf("Hooking a function");
	}

	assert(MH_EnableHook(MH_ALL_HOOKS) == MH_OK);
}

void CHookManager::Release()
{
	assert(MH_Uninitialize() == MH_OK);
}

std::vector<CHook*>& CHookManager::GetHooks()
{
	static std::vector<CHook*> s_Hooks = {};
	return s_Hooks;
}
