#include "Vars.h"

#include "../Utils/JSON/JSON.hpp"

#include <vector>
#include <typeinfo>
#include <fstream>
#include <iomanip>

void CFG::Save(const char* path)
{
	std::ofstream outputFile(path);

	if (!outputFile.is_open())
	{
		return;
	}

	nlohmann::json j{};

	for (const auto& Var : Vars)
	{
		if (Var.m_nTypeHash == typeid(bool).hash_code())
		{
			j[Var.m_szName] = *static_cast<bool*>(Var.m_pValuePointer);
		}

		if (Var.m_nTypeHash == typeid(int).hash_code())
		{
			j[Var.m_szName] = *static_cast<int*>(Var.m_pValuePointer);
		}

		if (Var.m_nTypeHash == typeid(float).hash_code())
		{
			j[Var.m_szName] = *static_cast<float*>(Var.m_pValuePointer);
		}

		if (Var.m_nTypeHash == typeid(std::string).hash_code())
		{
			j[Var.m_szName] = *static_cast<std::string*>(Var.m_pValuePointer);
		}

		if (Var.m_nTypeHash == typeid(Color_t).hash_code())
		{
			const auto clr = *static_cast<Color_t*>(Var.m_pValuePointer);
			j[Var.m_szName] = { clr.r, clr.g, clr.b, clr.a };
		}
	}

	outputFile << std::setw(4) << j;

	outputFile.close();
}

void CFG::Load(const char* path)
{
	std::ifstream inputFile(path);

	if (!inputFile.is_open())
	{
		return;
	}

	nlohmann::json j{};

	inputFile >> j;

	for (const auto& Var : Vars)
	{
		if (j.find(Var.m_szName) == j.end())
		{
			continue;
		}

		if (Var.m_nTypeHash == typeid(bool).hash_code())
		{
			*static_cast<bool*>(Var.m_pValuePointer) = j[Var.m_szName];
		}

		if (Var.m_nTypeHash == typeid(int).hash_code())
		{
			*static_cast<int*>(Var.m_pValuePointer) = j[Var.m_szName];
		}

		if (Var.m_nTypeHash == typeid(float).hash_code())
		{
			*static_cast<float*>(Var.m_pValuePointer) = j[Var.m_szName];
		}

		if (Var.m_nTypeHash == typeid(std::string).hash_code())
		{
			*static_cast<std::string*>(Var.m_pValuePointer) = j[Var.m_szName];
		}

		if (Var.m_nTypeHash == typeid(Color_t).hash_code())
		{
			Color_t clr = { j[Var.m_szName][0], j[Var.m_szName][1], j[Var.m_szName][2], j[Var.m_szName][3] };
			*static_cast<Color_t*>(Var.m_pValuePointer) = clr;
		}
	}

	inputFile.close();
}