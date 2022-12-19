#include "ResourceInfo.h"
#include "../SDK/SDK.h"
#include "../Features/Menu/Menu.h"

SResourceInfo::~SResourceInfo()
{
    if (this->m_Buffer)
    {
        FreeResource(this->m_Buffer);
    }
}

SResourceInfo* Resources::Get(const char* cName, const char* cType)
{
    auto* pInfo = new SResourceInfo();

    auto hMod = F::Menu.m_Module;

    const HRSRC hResourceInfo = FindResourceA(hMod, cName, cType);
    if (!hResourceInfo)
    {
        Util::PrintDebug("Unable to find resource %s (type: %s): %lu", cName, cType, GetLastError());
        return nullptr;
    }

    const HGLOBAL hResourceGlob = LoadResource(hMod, hResourceInfo);
    if (!hResourceGlob)
    {
        Util::PrintDebug("Unable to load resource %s (type: %s): %lu", cName, cType, GetLastError());
        return nullptr;
    }

    pInfo->m_Size = SizeofResource(hMod, hResourceInfo);
    pInfo->m_Buffer = LockResource(hResourceGlob);

    return pInfo;
}