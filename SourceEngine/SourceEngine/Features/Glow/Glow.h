#pragma once

#include "../Vars.h"

class CGlow
{
public:
	void Run();
	void Cleanup();
};

MAKE_FEATURE(CGlow, Glow);