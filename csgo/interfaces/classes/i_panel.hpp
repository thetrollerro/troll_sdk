#pragma once
#include "../../utilities/utilities.hpp"

class i_panel {
public:
	const char* get_name( unsigned int vguiPanel )
	{
		typedef const char* ( __thiscall* o_fn ) ( void*, unsigned int );
		return utilities::call_virtual< o_fn >( this, 36 ) ( this, vguiPanel );
	}
	const char* get_class_name( unsigned int vguiPanel )
	{
		typedef const char* ( __thiscall* o_fn ) ( void*, unsigned int );
		return utilities::call_virtual< o_fn >( this, 37 ) ( this, vguiPanel );
	}
};