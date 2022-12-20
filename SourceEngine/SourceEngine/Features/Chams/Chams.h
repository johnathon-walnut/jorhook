#pragma once

#include "../Vars.h"

class CChams
{
	IMaterial* m_pMatShaded, * m_pMatFlat;
public:
	void Run();
	void Cleanup();
};

MAKE_FEATURE(CChams, Chams);