#include "../features.hpp"

void prediction::start( c_usercmd* cmd ) {
	static int tick_base;
	static c_usercmd* last_cmd;

	if ( last_cmd ) {
		if ( last_cmd->hasbeenpredicted )
			tick_base = g_local->m_nTickBase( );
		else
			++tick_base;
	}

	// get random_seed as its 0 in clientmode->createmove
	const auto get_random_seed = [ & ] ( )
	{
		using o_fn = unsigned long( __cdecl* )( std::uintptr_t );
		static auto offset = utilities::find_sig_ida( "client.dll", "55 8B EC 83 E4 F8 83 EC 70 6A 58" );
		static auto MD5_PseudoRandom = reinterpret_cast< o_fn >( offset );
		return MD5_PseudoRandom( cmd->command_number ) & 0x7FFFFFFF;
	};

	last_cmd = cmd;

	/* backup globalvars */
	old_cur_time = interfaces::globals->cur_time;
	old_frame_time = interfaces::globals->frame_time;

	prediction_random_seed = get_random_seed( );

	/* simulate globalvars */
	interfaces::globals->cur_time = tick_base * interfaces::globals->interval_per_tick;
	interfaces::globals->frame_time = interfaces::globals->interval_per_tick;

	/* predict errors */
	interfaces::game_movement->start_track_prediction_errors( g_local );

	/* get move data */
	c_movedata data;
	memset( &data, 0, sizeof( data ) );

	/* fix movement/etc. */
	interfaces::move_helper->set_host( g_local );
	interfaces::prediction->setup_move( g_local, cmd, interfaces::move_helper, &data );
	interfaces::game_movement->process_movement( g_local, &data );
	interfaces::prediction->finish_move( g_local, cmd, &data );
}

void prediction::end( ) {
	/* stop predicting */
	interfaces::game_movement->finish_track_prediction_errors( g_local );
	interfaces::move_helper->set_host( nullptr );

	/* restore globalvars */
	interfaces::globals->cur_time = old_cur_time;
	interfaces::globals->frame_time = old_frame_time;
}
