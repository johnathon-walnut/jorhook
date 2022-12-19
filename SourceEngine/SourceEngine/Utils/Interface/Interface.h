#pragma once
#include <Windows.h>

class CInterface
{
private:
	typedef PVOID(*InstantiateInterface)();

	struct Interface_t
	{
		InstantiateInterface Interface;
		PCHAR szInterfaceName;
		Interface_t *NextInterface;
	};

public:
	PVOID Get(PCCH szModule, PCCH szObject);
};

namespace G { inline CInterface Interface; }