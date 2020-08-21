#pragma once
#include <cstdint>
#include "../utilities/utilities.hpp"
#include "../../utilities/utilities.hpp"

class c_convar {
public:
	__forceinline float get_float( void ) {
		int xord = ( int ) ( *( int* ) ( &f_value ) ^ ( uintptr_t ) this );
		return *( float* ) &xord;
	}

	__forceinline int get_int( void ) {
		int xord = ( int ) ( *( int* ) ( &n_value ) ^ ( uintptr_t ) this );
		return *( int* ) &xord;
	}

	bool get_bool( void ) {
		return !!get_int( );
	}

	void set_value( const char* value ) {
		using set_value_fn = void( __thiscall* )( void*, const char* );
		utilities::call_virtual<set_value_fn>( this, 14 )( this, value );
	}

	void set_value( float value ) {
		using set_value_fn = void( __thiscall* )( void*, float );
		utilities::call_virtual<set_value_fn>( this, 15 )( this, value );
	}

	void set_value( int value ) {
		using set_value_fn = void( __thiscall* )( void*, int );
		utilities::call_virtual<set_value_fn>( this, 16 )( this, value );
	}

	/*void set_value( color value ) {
		return ( ( void( __thiscall* )( void*, color ) ) get_vfunc( this, 17 ) )( this, value );
	}*/

	void null_callback( void ) {
		*( int* ) ( ( uintptr_t ) &change_callback_fn + 0xC ) = 0;
	}

	unsigned char pad_0x0[ 0x4 ];
	c_convar* next;
	int registered;
	char* name;
	char* help_string;
	int flags;
	unsigned char pad_0x18[ 0x4 ];
	c_convar* parent;
	char* default_value;
	char* string;
	int string_len;
	float f_value;
	int n_value;
	int has_min;
	float min_val;
	int has_max;
	float max_val;
	void* change_callback_fn;
};

class i_cvar {
public:
	c_convar* find_var( const char* convar_name ) {
		using find_var_fn = c_convar * ( __thiscall* )( void*, const char* );
		return utilities::call_virtual<find_var_fn>( this, 16 )( this, convar_name );
	}
};
