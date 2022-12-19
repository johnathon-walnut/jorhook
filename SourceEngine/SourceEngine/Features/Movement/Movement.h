#pragma once
#include "../Vars.h"

class CMovement
{
public:

	void DoBunnyhop(C_UserCmd* pCmd);
};

MAKE_FEATURE(CMovement, Movement);