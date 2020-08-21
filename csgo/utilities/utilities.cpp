#define NOMINMAX
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <Psapi.h>
#include "utilities.hpp"
#define INRANGE(x,a,b)   (x >= a && x <= b)
#define GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))

uintptr_t utilities::find_sig_ida( const char* module, const char* signature )
{
	/* antario? */
	const char* pat = signature;
	DWORD first_match = 0;
	DWORD range_start = ( DWORD ) GetModuleHandleA( module );
	MODULEINFO module_info;
	GetModuleInformation( GetCurrentProcess( ), reinterpret_cast< HMODULE >( range_start ), &module_info, sizeof( MODULEINFO ) );
	DWORD range_end = range_start + module_info.SizeOfImage;
	for ( DWORD pCur = range_start; pCur < range_end; pCur++ )
	{
		if ( !*pat )
			return first_match;

		if ( *( PBYTE ) pat == '\?' || *( BYTE* ) pCur == GET_BYTE( pat ) )
		{
			if ( !first_match )
				first_match = pCur;

			if ( !pat[ 2 ] )
				return first_match;

			if ( *( PWORD ) pat == '\?\?' || *( PBYTE ) pat != '\?' )
				pat += 3;

			else
				pat += 2;
		}
		else
		{
			pat = signature;
			first_match = 0;
		}
	}
	return NULL;
}

DWORD utilities::find_sig_byte( const char* module_name, const BYTE* mask, const char* mask_string )
{
	/* get module addresses */
	const unsigned int module_address = reinterpret_cast< unsigned int >( GetModuleHandleA( module_name ) );

	/// Get module information to the size
	MODULEINFO module_info;
	GetModuleInformation( GetCurrentProcess( ), reinterpret_cast< HMODULE >( module_address ), &module_info, sizeof( MODULEINFO ) );

	auto is_correct_mask = [ ] ( const unsigned char* data, const unsigned char* mask, const char* mask_string ) -> bool
	{
		for ( ; *mask_string; ++mask_string, ++mask, ++data )
			if ( *mask_string == 'x' && *mask != *data )
				return false;

		return ( *mask_string ) == 0;
	};

	/// Iterate until we find a matching mask
	for ( unsigned int c = 0; c < module_info.SizeOfImage; c += 1 )
	{
		/// does it match?
		if ( is_correct_mask( reinterpret_cast< unsigned char* >( module_address + c ), mask, mask_string ) )
			return ( module_address + c );
	}

	return 0;
}