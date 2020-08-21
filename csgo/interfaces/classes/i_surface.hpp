#pragma once
#include "../../utilities/utilities.hpp"

class i_surface {
public:
	void unlock_cursor( ) {
		using o_fn = void( __thiscall* )( i_surface* );
		utilities::call_virtual<o_fn>( this, 66 )( this );
	}

	void get_cursor_pos( int& x, int& y ) {
		using get_cursor_pos_fn = void( __thiscall* )( void*, int&, int& );
		utilities::call_virtual< get_cursor_pos_fn >( this, 100 )( this, x, y );
	}

	void draw_line( int x0, int y0, int x1, int y1 ) {
		using original_fn = void( __thiscall* )( PVOID, int, int, int, int );
		utilities::call_virtual< original_fn >( this, 19 )( this, x0, y0, x1, y1 );
	}
};