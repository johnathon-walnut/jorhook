#pragma once
#include "../../SDK/SDK.h"

#include <functional>

enum struct EItemType {
	DEFAULT,
	INT,
	FLOAT,
	BOOL,
	COLOR,
	KEY,
	BUTTON
};

class CItemBase
{
public:
	std::string m_Name = {};
	EItemType e_Type = EItemType::DEFAULT;
	CItemBase(EItemType type, const std::string &name) : e_Type(type), m_Name(name) {};
};

class CItemButton : public CItemBase
{
public:
	std::function<void()> m_Ptr = {};
	float m_flTimePressed = 0.f;
	CItemButton(const std::string& name, std::function<void()> ptr) : CItemBase(EItemType::BUTTON, name), m_Ptr(ptr)
	{
	}
};

class CItemInt : public CItemBase
{
public:
	int *m_Ptr = nullptr;
	std::vector<std::pair<int, std::string>> m_Aliases = {};
	int m_Min = std::numeric_limits<int>::min();
	int m_Max = std::numeric_limits<int>::max();

	int m_AliasIdx = 0;

	CItemInt(const std::string &name,
		int *ptr,
		std::vector<std::pair<int, std::string>> aliases = {},
		int min = std::numeric_limits<int>::min(),
		int max = std::numeric_limits<int>::max())
		: CItemBase(EItemType::INT, name), m_Ptr(ptr), m_Aliases(aliases), m_Min(min), m_Max(max)
	{
		if (!m_Aliases.empty())
		{
			bool Found = false;

			for (const auto &Alias : this->m_Aliases)
			{
				if (*reinterpret_cast<int *>(this->m_Ptr) == Alias.first) {
					this->m_AliasIdx = Alias.first;
					Found = true;
					break;
				}
			}

			if (!Found)
				*reinterpret_cast<int *>(this->m_Ptr) = this->m_Aliases.at(0).first;
		}
	}
};

class CItemKey : public CItemBase
{
public:
	int* m_Ptr = nullptr;
	bool m_bActive = false;
	float m_flTimeActivated = 0.f;

	CItemKey(const std::string& name, int* ptr) : CItemBase(EItemType::KEY, name), m_Ptr(ptr)
	{
	}

	inline static std::string KeyCodeToString(int virtualKey)
	{
		switch (virtualKey)
		{
			case VK_LBUTTON: return "LButton";
			case VK_RBUTTON: return "RButton";
			case VK_MBUTTON: return "MButton";
			case VK_XBUTTON1: return "XButton1";
			case VK_XBUTTON2: return "XButton2";
			case VK_SPACE: return "Space";
			case 0x0: return "None";
		}

		CHAR output[32] = { "\0" };

		if (const int result = GetKeyNameTextA(MapVirtualKeyA(virtualKey, MAPVK_VK_TO_VSC) << 16, output, 16))
		{
			return output;
		}

		return "Unknown";
	}
};

enum class EClrType
{
	r, g, b, a
};

class CItemClr : public CItemBase
{
public:
	Color_t* m_Ptr = nullptr;
	EClrType m_Type;
	std::vector<std::pair<int, std::string>> m_Aliases = {};
	int m_Min = std::numeric_limits<int>::min();
	int m_Max = std::numeric_limits<int>::max();

	int m_AliasIdx = 0;

	CItemClr(const std::string& name, Color_t* ptr, EClrType type, std::vector<std::pair<int, std::string>> aliases = {},
			 int min = 0, int max = 255) : CItemBase(EItemType::COLOR, name), m_Type(type), m_Ptr(ptr), m_Aliases(aliases), m_Min(min), m_Max(max)
	{
		if (!m_Aliases.empty())
		{
			bool Found = false;

			for (const auto& Alias : this->m_Aliases)
			{
				if (*reinterpret_cast<int*>(this->m_Ptr) == Alias.first)
				{
					this->m_AliasIdx = Alias.first;
					Found = true;
					break;
				}
			}

			if (!Found)
				*reinterpret_cast<int*>(this->m_Ptr) = this->m_Aliases.at(0).first;
		}
	}
};

class CItemFloat : public CItemBase
{
public:
	float *m_Ptr = nullptr;
	float m_Step = 1.0f;
	float m_Min = std::numeric_limits<float>::min();
	float m_Max = std::numeric_limits<float>::max();

	CItemFloat(const std::string &name,
		float *ptr,
		float step = 1.0f,
		float min = std::numeric_limits<float>::min(),
		float max = std::numeric_limits<float>::max())
		: CItemBase(EItemType::FLOAT, name), m_Ptr(ptr), m_Step(step), m_Min(min), m_Max(max) {}
};

class CItemBool : public CItemBase
{
public:
	bool *m_Ptr = nullptr;
	CItemBool(const std::string &name, bool *ptr) : CItemBase(EItemType::BOOL, name), m_Ptr(ptr) {}
};

class CItemGroup
{
public:
	std::string m_Name = {};
	std::vector<CItemBase *> m_Items = {};
	bool m_Open = false;
	EItemType e_Type = EItemType::DEFAULT;
};

class CItemClrGroup : public CItemGroup
{
public:
	Color_t* m_Clr;
};

class CItemList
{
public:
	std::string m_Name = {};
	std::vector<CItemGroup *> m_ItemGroups = {};

	int m_X, m_Y;
	int m_Height = 650;
	POINT m_Delta;
	bool m_bDrag = false;
	bool m_bMove = false;

	void Drag(int mousex, int mousey);
};

class CMenu
{
private:
	std::vector<CItemList *> m_ItemLists = {};
	void CreateLists();

public:
	bool m_Open = false;
	bool m_OnAimbotFOV = false;

	WNDPROC m_WndProc;
	HWND m_GameHWND;
	HMODULE m_Module;

	~CMenu();
	void Run();
};

MAKE_FEATURE(CMenu, Menu);