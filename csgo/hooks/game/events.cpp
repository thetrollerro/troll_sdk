#include "../hooks.hpp"

template<class t>
static t* find_hud_element( const char* name )
{
	static auto pthis = *reinterpret_cast< DWORD** >( utilities::find_sig_ida( "client.dll", "B9 ? ? ? ? E8 ? ? ? ? 8B 5D 08" ) + 1 );

	static auto find_hud_element = reinterpret_cast< DWORD( __thiscall* )( void*, const char* ) >( utilities::find_sig_ida( "client.dll", "55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39 77 28" ) );
	return ( t* ) find_hud_element( pthis, name );
}

void hooks::events::fire_game_event( i_game_event* event ) {
	if ( !event || !g_local || !interfaces::engine->is_in_game( ) ) return;

	/* vars */
	auto attacker = interfaces::entity_list->get_client_entity( interfaces::engine->get_player_for_userid( event->get_int( "attacker" ) ) );
	auto pl = ( c_base_entity* ) interfaces::entity_list->get_client_entity( interfaces::engine->get_player_for_userid( event->get_int( "userid" ) ) );

	if ( !attacker || !pl ) return;

	auto name = event->get_name( );
	if ( !strcmp( name, "player_hurt" ) ) {
		if ( attacker != g_local ) return;

	}
	if ( !strcmp( name, "player_death" ) ) {
		if ( attacker != g_local ) {

		}
		else {
		
		}
	}
	if ( !strcmp( name, "weapon_fire" ) ) {
		if ( pl != g_local ) return;

	}
	if ( strstr( name, "round_start" ) ) {
		
	}
	if ( strstr( name, "item_purchase" ) ) {

	}
};