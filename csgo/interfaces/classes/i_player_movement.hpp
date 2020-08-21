#pragma once
#include "../../sdk/math/vector3d.hpp"
#include "../../sdk/classes/c_usercmd.hpp"
#include "../../utilities/utilities.hpp"

class c_base_entity;
class c_movedata {
public:
	bool m_first_run_of_functions : 1;
	bool m_game_code_moved_player : 1;
	int m_player_handle;
	int m_impulse_command;
	vec3_t m_view_angles;
	vec3_t m_abs_view_angles;
	int m_buttons;
	int m_old_buttons;
	float m_forward_move;
	float m_side_move;
	float m_up_move;
	float m_max_speed;
	float m_client_max_speed;
	vec3_t m_velocity;
	vec3_t m_angles;
	vec3_t m_old_angles;
	float m_out_step_height;
	vec3_t m_out_wish_vel;
	vec3_t m_out_jump_vel;
	vec3_t m_constraint_center;
	float m_constraint_radius;
	float m_constraint_width;
	float m_constraint_speed_factor;
	float m_flunknown[ 5 ];
	vec3_t m_abs_origin;
};


class virtual_game_movement {
public:
	virtual			~virtual_game_movement( void ) { }

	virtual void	          process_movement( c_base_entity* player, c_movedata* move ) = 0;
	virtual void	          reset( void ) = 0;
	virtual void	          start_track_prediction_errors( c_base_entity* player ) = 0;
	virtual void	          finish_track_prediction_errors( c_base_entity* player ) = 0;
	virtual void	          diff_print( char const* fmt, ... ) = 0;
	virtual vec3_t const& get_player_mins( bool ducked ) const = 0;
	virtual vec3_t const& get_player_maxs( bool ducked ) const = 0;
	virtual vec3_t const& get_player_view_offset( bool ducked ) const = 0;
	virtual bool		        is_moving_player_stuck( void ) const = 0;
	virtual c_base_entity* get_moving_player( void ) const = 0;
	virtual void		        unblock_pusher( c_base_entity* player, c_base_entity* pusher ) = 0;
	virtual void            setup_movement_bounds( c_movedata* move ) = 0;
};

class i_player_movement
	: public virtual_game_movement {
public:
	virtual ~i_player_movement( void ) { }
};