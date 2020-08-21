#include "../hooks.hpp"

void __fastcall hooks::fire_game_event::hook( void* ecx, void* edx ) {
	if ( !g_local || !g_local->is_alive( ) )
		return o_fireevent( ecx, edx );

	struct event_t {
	public:
		uint8_t pad0x04[ 4 ];
		float delay;
		uint8_t pad0x48[ 48 ];
		event_t* next;
	};
	auto event = *( event_t** ) ( uintptr_t( interfaces::clientstate ) + 0x4E64 );
	while ( event ) {
		event->delay = 0.0f;
		event = event->next;
	}

	return o_fireevent( ecx, edx );
}