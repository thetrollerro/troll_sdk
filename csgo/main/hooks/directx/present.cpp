#include "../hooks.hpp"


long __stdcall hooks::present::hook( IDirect3DDevice9* dev, RECT* source_rect, RECT* dust_rect, HWND dest_window_override, RGNDATA* dirty_region ) {
	/* call dx features */
	dx_things( dev );

	return o_present( dev, source_rect, dust_rect, dest_window_override, dirty_region );
}