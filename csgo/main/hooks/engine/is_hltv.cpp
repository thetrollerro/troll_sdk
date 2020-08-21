#include "../hooks.hpp"

bool __fastcall hooks::is_hltv::hook( uintptr_t ecx, uintptr_t edx )
{
	static auto ptr_accumulate_layers = reinterpret_cast< void* > ( utilities::find_sig_ida( "client.dll", "84 C0 75 0D F6 87" ) );
	static auto setupvelocity_call = reinterpret_cast< void* > ( utilities::find_sig_ida( "client.dll", "84 C0 75 38 8B 0D ? ? ? ? 8B 01 8B 80 ? ? ? ? FF D0" ) );

	if ( ( uintptr_t ) _ReturnAddress( ) == ( uintptr_t ) ptr_accumulate_layers )
		return true;

	if ( ( uintptr_t ) _ReturnAddress( ) == ( uintptr_t ) setupvelocity_call )
		return true;

	return o_ishltv( ecx, edx );
}