#pragma once

#include "../../Includes/Includes.h"
#include <stdint.h>

enum types_t
{
	TYPE_NONE = 0,
	TYPE_STRING,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_PTR,
	TYPE_WSTRING,
	TYPE_COLOUR,
	TYPE_UINT64,
	TYPE_NUMTYPES,
};

class KeyValues
{
private:
	int m_iKeyName;
	char* m_sValue;
	wchar_t* m_wsValue;

	union
	{
		int m_iValue;
		float m_flValue;
		void* m_pValue;
		unsigned char m_Colour[4];
	};

	char m_iDataType;
	char m_bHasEscapeSequences;
	char m_bEvaluateConditionals;
	char unused[1];

	KeyValues* m_pPeer;
	KeyValues* m_pSub;
	KeyValues* m_pChain;

public:
	bool LoadFromBuffer(char const* resource_name, const char* buffer, void* file_system = 0, const char* path_id = 0);
	void Initialize(char* name);
	KeyValues(const char* name);
	KeyValues* FindKey(const char* keyName, bool bCreate = false);
	KeyValues* AddSubkey(KeyValues* pSubkey);
	int GetInt(const char* keyName, int defaultValue = 0);
	uint64_t GetUint64(const char* keyName, uint64_t defaultValue = 0);
	float GetFloat(const char* keyName, float defaultValue = 0.0f);
	const char* GetString(const char* keyName, const char* defaultValue = "");
	const wchar_t* GetWString(const char* keyName, const wchar_t* defaultValue = L"");
	void* GetPtr(const char* keyName, void* defaultValue = (void*)0);
	bool GetBool(const char* keyName, bool defaultValue = false);
	Color_t GetColour(const char* keyName);
	bool IsEmpty(const char* keyName);

	void SetWString(const char* keyName, const wchar_t* value);
	void SetString(const char* keyName, const char* value);
	void SetInt(const char* keyName, int value);
	void SetUint64(const char* keyName, uint64_t value);
	void SetFloat(const char* keyName, float value);
	void SetPtr(const char* keyName, void* value);
	void SetColour(const char* keyName, Color_t value);
	void SetBool(const char* keyName, bool value) { SetInt(keyName, value ? 1 : 0); }
};

#define ARRAYSIZE(A)    RTL_NUMBER_OF_V2(A)
#define _ARRAYSIZE(A)   RTL_NUMBER_OF_V1(A)
#define Q_ARRAYSIZE(p)		ARRAYSIZE(p)

inline int V_UnicodeToUTF8(const wchar_t* pUnicode, char* pUTF8, int cubDestSizeInBytes)
{
	if (cubDestSizeInBytes > 0)
	{
		pUTF8[0] = 0;
	}

	int cchResult = WideCharToMultiByte(CP_UTF8, 0, pUnicode, -1, pUTF8, cubDestSizeInBytes, NULL, NULL);

	if (cubDestSizeInBytes > 0)
	{
		pUTF8[cubDestSizeInBytes - 1] = 0;
	}

	return cchResult;
}

inline int V_UTF8ToUnicode(const char* pUTF8, wchar_t* pwchDest, int cubDestSizeInBytes)
{
	if (!pUTF8)
		return 0;

	pwchDest[0] = 0;
	int cchResult = MultiByteToWideChar(CP_UTF8, 0, pUTF8, -1, pwchDest, cubDestSizeInBytes / sizeof(wchar_t));
	pwchDest[(cubDestSizeInBytes / sizeof(wchar_t)) - 1] = 0;
	return cchResult;
}