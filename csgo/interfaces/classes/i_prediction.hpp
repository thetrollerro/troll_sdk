#pragma once
#include "../../utilities/utilities.hpp"
#include "../../sdk/math/vector3d.hpp"

class c_move_helper {
public:
	virtual void pad00( ) = 0;
	virtual void set_host( c_base_entity* host ) = 0;
	virtual void pad01( ) = 0;
	virtual void pad02( ) = 0;
	virtual void process_impacts( ) = 0;
};
class c_base_entity;
class i_prediction {
public:
	void get_local_viewangles( vec3_t& angle ) {
		using fn = void( __thiscall* )( void*, vec3_t& );
		utilities::call_virtual< fn >( this, 12 )( this, angle );
	}

	void set_local_viewangles( vec3_t& angle ) {
		using fn = void( __thiscall* )( void*, vec3_t& );
		utilities::call_virtual< fn >( this, 13 )( this, angle );
	}

	void update( int start_frame, bool valid_frame, int inc_ack, int out_cmd ) {
		using fn = void( __thiscall* )( void*, int, bool, int, int );
		utilities::call_virtual< fn >( this, 3 )( this, start_frame, valid_frame, inc_ack, out_cmd );
	}

	void check_moving_ground( c_base_entity* player, double frametime ) {
		using fn = void( __thiscall* )( void*, c_base_entity*, double );
		utilities::call_virtual< fn >( this, 18 )( this, player, frametime );
	}

	void setup_move( c_base_entity* player, c_usercmd* ucmd, c_move_helper* helper, void* movedata ) {
		using fn = void( __thiscall* )( void*, c_base_entity*, c_usercmd*, c_move_helper*, void* );
		utilities::call_virtual< fn >( this, 20 )( this, player, ucmd, helper, movedata );
	}

	void finish_move( c_base_entity* player, c_usercmd* ucmd, void* movedata ) {
		using fn = void( __thiscall* )( void*, c_base_entity*, c_usercmd*, void* );
		utilities::call_virtual< fn >( this, 21 )( this, player, ucmd, movedata );
	}

	uint8_t pad_0x1[ 0x8 ];
	bool m_in_prediction;
	uint8_t pad_0x2[ 0x1 ];
	bool m_engine_paused;
	uint8_t pad_0x3[ 13 ];
	bool m_is_first_time_predicted;
};