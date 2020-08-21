#pragma once
#include "../../utilities/utilities.hpp"

class i_surface {
public:
	void unlock_cursor( ) {
		using o_fn = void( __thiscall* )( i_surface* );
		return utilities::call_virtual<o_fn>( this, 66  )( this );
	}
};