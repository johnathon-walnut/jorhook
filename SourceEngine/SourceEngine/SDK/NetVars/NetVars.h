#pragma once
#include "../Interfaces/Interfaces.h"
#include <fstream>

inline int GetOffset(RecvTable* pTable, const char* szNetVar)
{
	for (int i = 0; i < pTable->m_nProps; i++)
	{
		RecvProp Prop = pTable->m_pProps[i];

		if (std::string_view(Prop.m_pVarName).compare(szNetVar) == 0)
		{
			return Prop.GetOffset();
		}

		if (auto DataTable = Prop.GetDataTable())
		{
			if (auto nOffset = GetOffset(DataTable, szNetVar))
			{
				return nOffset + Prop.GetOffset();
			}
		}
	}

	return 0;
}

inline int GetNetVar(const char* szClass, const char* szNetVar)
{
	ClientClass* pClasses = I::Client->GetAllClasses();

	for (auto pCurrNode = pClasses; pCurrNode; pCurrNode = pCurrNode->m_pNext)
	{
		if (std::string_view(szClass).compare(pCurrNode->m_pNetworkName) == 0)
		{
			return GetOffset(pCurrNode->m_pRecvTable, szNetVar);
		}
	}

	return 0;
}

#define NETVAR(_name, type, table, name) inline type &_name() \
{ \
	static int offset = GetNetVar(table, name); \
	return *reinterpret_cast<type *>(reinterpret_cast<DWORD>(this) + offset); \
}

#define NETVAR_OFFSET_FROM(_name, type, table, name, addition) inline type &_name() \
{ \
	static int offset = GetNetVar(table, name); \
	return *reinterpret_cast<type *>(reinterpret_cast<DWORD>(this) + offset + addition); \
}

#define NETVAR_OFFSET_PURE(_name, type, offset) inline type &_name() \
{ \
	return *reinterpret_cast<type *>(reinterpret_cast<DWORD>(this) + offset); \
}

namespace N
{
	inline std::ofstream File;
	inline const char* szClassName;

	void DumpTable(RecvTable* pTable, int nDepth, int classid);
	void DumpTables();
}
