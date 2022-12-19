#pragma once

struct SResourceInfo
{
    unsigned long m_Size;
    void* m_Buffer;

    ~SResourceInfo();
};

namespace Resources
{
    SResourceInfo* Get(const char* cName, const char* cType);
}
