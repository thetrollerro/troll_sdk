#include "../hooks.hpp"

long __stdcall hooks::reset::hook( IDirect3DDevice9* dev, D3DPRESENT_PARAMETERS* params ) {
	/* destroy fonts */
	render::destroy_fonts( );

	if ( !menu::d3d_init )
		return o_reset( dev, params );

	/* invalidate device object */
	ImGui_ImplDX9_InvalidateDeviceObjects( );

	auto hr = o_reset( dev, params );

	if ( SUCCEEDED( hr ) ) {
		/* recreate device objects */
		ImGui_ImplDX9_CreateDeviceObjects( );

		/* recreate fonts */
		render::create_fonts( );
	}

	return hr;
}