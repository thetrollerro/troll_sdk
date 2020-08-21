#include "../hooks.hpp"

void __fastcall hooks::update_clientside_animation::hook( void* ecx, void* edx ) {
	auto e = ( c_base_entity* ) ecx;

	if ( !e || !e->is_alive( ) || !e->is_player( ) || e->is_dormant( ) ) {
		o_updateclientanim( ecx, edx );
		return;
	}

    /* backup */
    const auto o_curtime = interfaces::globals->cur_time;
    const auto o_realtime = interfaces::globals->realtime;
    const auto o_interpolationamount = interfaces::globals->interpolation_amount;
    const auto o_tickcount = interfaces::globals->tick_count;
    const auto o_absorigin = e->abs_origin( );

    /* update animations */
    interfaces::globals->cur_time = e->m_flSimulationTime( );
    interfaces::globals->realtime = e->m_flSimulationTime( );
    interfaces::globals->interpolation_amount = 0;
    interfaces::globals->tick_count = TIME_TO_TICKS( e->m_flSimulationTime( ) );
    e->set_abs_origin( e->m_vecOrigin( ) );

    /* update animations */
    o_updateclientanim( ecx, edx );

    /* restore */
    interfaces::globals->cur_time = o_curtime;
    interfaces::globals->realtime = o_realtime;
    interfaces::globals->interpolation_amount = o_interpolationamount;
    interfaces::globals->tick_count = o_tickcount;
    e->set_abs_origin( o_absorigin );

	o_updateclientanim( ecx, edx );
}