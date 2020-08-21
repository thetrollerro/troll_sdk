#include "../hooks.hpp"

/* get imgui input handler */
extern LRESULT ImGui_ImplDX9_WndProcHandler( HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam );

long hooks::wndproc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	/* wndproc handler */ {
		switch ( msg ) {
		case WM_LBUTTONDOWN:
			hooks::pressed_keys[ VK_LBUTTON ] = true;
			break;
		case WM_LBUTTONUP:
			hooks::pressed_keys[ VK_LBUTTON ] = false;
			break;
		case WM_RBUTTONDOWN:
			hooks::pressed_keys[ VK_RBUTTON ] = true;
			break;
		case WM_RBUTTONUP:
			hooks::pressed_keys[ VK_RBUTTON ] = false;
			break;
		case WM_MBUTTONDOWN:
			hooks::pressed_keys[ VK_MBUTTON ] = true;
			break;
		case WM_MBUTTONUP:
			hooks::pressed_keys[ VK_MBUTTON ] = false;
			break;
		case WM_XBUTTONDOWN: {
			UINT button = GET_XBUTTON_WPARAM( wparam );
			if ( button == XBUTTON1 ) {
				hooks::pressed_keys[ VK_XBUTTON1 ] = true;
			}
			else if ( button == XBUTTON2 ) {
				hooks::pressed_keys[ VK_XBUTTON2 ] = true;
			}
			break;
		}
		case WM_XBUTTONUP: {
			UINT button = GET_XBUTTON_WPARAM( wparam );
			if ( button == XBUTTON1 ) {
				hooks::pressed_keys[ VK_XBUTTON1 ] = false;
			}
			else if ( button == XBUTTON2 ) {
				hooks::pressed_keys[ VK_XBUTTON2 ] = false;
			}
			break;
		}
		case WM_KEYDOWN:
			hooks::pressed_keys[ wparam ] = true;
			break;
		case WM_KEYUP:
			hooks::pressed_keys[ wparam ] = false;
			break;
		default: break;
		}
	}

	/* open menu */ {
		static bool m_pressed = false;
		const bool m_held = GetAsyncKeyState( VK_INSERT );
		if ( m_pressed != m_held ) {

			if ( m_held ) {
				menu::opened = !menu::opened;
			}

			m_pressed = m_held;
		}
	}

	if ( menu::d3d_init && menu::opened && ImGui_ImplDX9_WndProcHandler( hwnd, msg, wparam, lparam ) )
		return true;

	return CallWindowProcA( hooks::orig_wnd_proc, hwnd, msg, wparam, lparam );
}