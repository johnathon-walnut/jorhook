#include "HookManager.h"

CHook::CHook(std::string sHookName, void* pInitFunction)
{
	m_pInitFunction = pInitFunction;
	this->m_sHookName = sHookName;

	F::HookManager.GetMapHooks()[sHookName] = this;
}

void CHookManager::Initialize()
{
	assert(MH_Initialize() == MH_OK);
	
	for (const auto& Hook : GetMapHooks())
	{
		I::CVars->ConsolePrintf("[!] Hooking %s", Hook.first.c_str());
		reinterpret_cast<void(__cdecl*)()>(Hook.second->m_pInitFunction)();
	}

	assert(MH_EnableHook(MH_ALL_HOOKS) == MH_OK);
}

void CHookManager::Release()
{
	assert(MH_Uninitialize() == MH_OK);
}