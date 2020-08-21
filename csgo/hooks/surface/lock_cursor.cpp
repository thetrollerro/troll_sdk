#include "../hooks.hpp"

void __fastcall hooks::lock_cursor::hook( void* ecx, void* edx ) {
	if ( menu::opened ) {
		interfaces::surface->unlock_cursor( );
		interfaces::inputsystem->reset_input_state( );
		return;
	}

	o_lockcursor( interfaces::surface, edx );
}