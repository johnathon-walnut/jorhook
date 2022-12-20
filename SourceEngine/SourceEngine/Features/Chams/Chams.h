#pragma once

#include "../Vars.h"

class CChams
{
	IMaterial* m_pMatShaded, * m_pMatFlat, * m_pMatShiny;
public:
	void Run();
	void Cleanup();
};

MAKE_FEATURE(CChams, Chams);