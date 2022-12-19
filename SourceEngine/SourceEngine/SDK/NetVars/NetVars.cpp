#include "NetVars.h"

void N::DumpTable(RecvTable* pTable, int nDepth, int classid)
{
	if (!pTable)
		return;

	const char* Types[7] = { "int", "float", "Vector", "Vector2D", "const char *", "Array", "void *" };

	if (nDepth == 0)
	{
		File << "// Class ID: " << classid << "\n";
		File << "class " << szClassName << "\n{\npublic:\n";
	}

	for (int n = 0; n < pTable->m_nProps; n++)
	{
		RecvProp* pProp = &pTable->m_pProps[n];

		if (!pProp)
			continue;

		std::string_view sVarName(pProp->m_pVarName);

		if (!sVarName.find("baseclass") || !sVarName.find("0") || !sVarName.find("1") || !sVarName.find("2"))
			continue;

		const char* szType = Types[pProp->m_RecvType];

		if (sVarName.find("m_b") == 0 && pProp->m_RecvType == 0)
			szType = "bool";

		if (pProp->GetOffset())
			File << "\tNETVAR(" << sVarName << ", " << szType << ", \"" << szClassName << "\", \"" << sVarName << "\");\n";

		if (auto DataTable = pProp->GetDataTable())
			DumpTable(DataTable, nDepth + 1, classid);
	}

	if (nDepth == 0)
		File << "};\n";
}

void N::DumpTables()
{
	File.open("NETVAR_DUMP_NEW.h");

	for (ClientClass* pClass = I::Client->GetAllClasses(); pClass; pClass = pClass->m_pNext)
	{
		szClassName = pClass->m_pNetworkName;
		DumpTable(pClass->m_pRecvTable, 0, pClass->m_ClassID);
	}

	File.close();

	File.open("CLASSID_DUMP_NEW.h");

	File << "enum EClassID {\n";

	for (ClientClass* pClass = I::Client->GetAllClasses(); pClass; pClass = pClass->m_pNext)
	{
		szClassName = pClass->m_pNetworkName;
		File << "\t" << szClassName << " = " << pClass->m_ClassID << ";\n";
	}

	File << "};";

	File.close();
}