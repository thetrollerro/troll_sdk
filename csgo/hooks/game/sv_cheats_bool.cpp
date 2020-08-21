#include "../hooks.hpp"

bool __fastcall hooks::sv_cheats_bool::hook( void* ecx, void* edx ) {
	static auto cam_think = utilities::find_sig_ida( "client.dll", "85 C0 75 30 38 86" );

	if ( _ReturnAddress( ) == ( void* ) cam_think )
		return true;

	return o_svcheatsbool( ecx, edx );
}