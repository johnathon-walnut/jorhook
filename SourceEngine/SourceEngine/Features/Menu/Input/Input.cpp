#include "Input.h"

void C_Input::Update()
{
	for (auto &Key : G::Input.m_Keyboard) {
		if (Key.second != EKeyState::NONE)
		{
			Key.second = EKeyState::HELD;
		}
	}

	if (m_RMouse != EKeyState::NONE)
	{
		m_RMouse = EKeyState::HELD;
	}

	if (m_LMouse != EKeyState::NONE)
	{
		m_LMouse = EKeyState::HELD;
	}

	if (m_MMouse != EKeyState::NONE)
	{
		m_MMouse = EKeyState::HELD;
	}
}

EKeyState C_Input::GetKey(int key)
{
	return m_Keyboard[key];
}

EKeyState C_Input::GetMouse(int key)
{
	switch (key)
	{
		case VK_RBUTTON: { return m_RMouse; }
		case VK_LBUTTON: { return m_LMouse; }
		case VK_MBUTTON: { return m_MMouse; }
	}

	return {};
}