#include "../hooks.hpp"

void __fastcall hooks::override_view::hook( void* ecx, void* edx, view_setup_t* view )
{
	if ( !interfaces::engine->is_in_game( ) || !g_local || !g_local->is_alive( ) ) {
		o_overrideview( interfaces::clientmode, edx, view );
		return;
	}

	o_overrideview( interfaces::clientmode, edx, view );
}