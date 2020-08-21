#pragma once

class i_client_entity;
class view_setup_t;
class c_base_entity;
class i_panel;

class i_client_mode {
public:
	virtual ~i_client_mode( )
	{
	}

	virtual int client_mode_cs_normal( void* ) = 0;
	virtual void init( ) = 0;
	virtual void init_viewport( ) = 0;
	virtual void shutdown( ) = 0;
	virtual void enable( ) = 0;
	virtual void disable( ) = 0;
	virtual void layout( ) = 0;
	virtual i_panel* get_viewport( ) = 0;
	virtual void* get_viewport_animatio_ncontroller( ) = 0;
	virtual void process_input( bool bactive ) = 0;
	virtual bool should_draw_detail_objects( ) = 0;
	virtual bool should_draw_entity( c_base_entity* entity ) = 0;
	virtual bool should_draw_local_player( c_base_entity* player ) = 0;
	virtual bool should_draw_particles( ) = 0;
	virtual bool should_draw_fog( void ) = 0;
	virtual void override_view( view_setup_t* setup ) = 0;
	virtual int key_input( int down, int key, const char* current_Binding ) = 0;
	virtual void start_message_mode( int type ) = 0;
	virtual i_panel* get_message_panel( ) = 0;
	virtual void override_mouse_input( float* x, float* y ) = 0;
	virtual bool create_move( float input_sample_time, void* usercmd ) = 0;
	virtual void level_init( const char* new_map ) = 0;
	virtual void level_shutdown( void ) = 0;
};