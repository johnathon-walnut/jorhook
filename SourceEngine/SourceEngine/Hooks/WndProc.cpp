#include "Hook.h"

#include "../Features/Menu/Menu.h"
#include "../Features/Menu/Input/Input.h"

namespace H
{
	namespace WndProc
	{
		void Initialize();
		inline CHook Hook("WndProc", Initialize);
		LRESULT CALLBACK Detour(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	}
}

void H::WndProc::Initialize()
{
	while (!F::Menu.m_GameHWND)
	{
		F::Menu.m_GameHWND = FindWindowW(L"Valve001", nullptr);
		Sleep(100);
	}

	F::Menu.m_WndProc = reinterpret_cast<WNDPROC>(SetWindowLongW(F::Menu.m_GameHWND, GWL_WNDPROC, reinterpret_cast<LONG>(Detour)));
}

LRESULT CALLBACK H::WndProc::Detour(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_KEYDOWN:
		{
			G::Input.m_Keyboard[wParam] = EKeyState::PRESSED;
			break;
		}

		case WM_KEYUP:
		{
			G::Input.m_Keyboard[wParam] = EKeyState::NONE;
			break;
		}

		case WM_RBUTTONDOWN:
		{
			if (wParam & MK_RBUTTON)
				G::Input.m_RMouse = EKeyState::PRESSED;

			break;
		}

		case WM_LBUTTONDOWN:
		{
			if (wParam & MK_LBUTTON)
				G::Input.m_LMouse = EKeyState::PRESSED;

			break;
		}

		case WM_MBUTTONDOWN:
		{
			if (wParam & MK_MBUTTON)
				G::Input.m_MMouse = EKeyState::PRESSED;

			break;
		}

		case WM_RBUTTONUP:
		{
			G::Input.m_RMouse = EKeyState::NONE;
			break;
		}

		case WM_LBUTTONUP:
		{
			G::Input.m_LMouse = EKeyState::NONE;
			break;
		}

		case WM_MBUTTONUP:
		{
			G::Input.m_MMouse = EKeyState::NONE;
			break;
		}

		case WM_MOUSEWHEEL:
		{
			G::Input.m_Wheel = ((int)wParam < 0 ? EScrollWheelState::UP : EScrollWheelState::DOWN);
			break;
		}
	}

	if (F::Menu.m_Open && (I::Engine->Con_IsVisible() || I::EngineVGui->IsGameUIVisible()))
	{
		return 1;
	}

	return CallWindowProcW(F::Menu.m_WndProc, hwnd, uMsg, wParam, lParam);
}

