#include "../hooks.hpp"

void __fastcall hooks::do_extra_bones_processing::hook( void* ecx, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 )
{
	const auto e = ( c_base_entity* ) ecx;
	if ( !e ) {
		o_extrabonesprocessing( ecx, edx, a2, a3, a4, a5, a6, a7 );
		return;
	}

	auto animstate = e->get_animstate( );

	if ( !animstate || !animstate->m_entity ) {
		o_extrabonesprocessing( ecx, edx, a2, a3, a4, a5, a6, a7 );
		return;
	}

	/* prevent call to do_procedural_foot_plant */
	const auto o_on_ground = animstate->m_on_ground;

	animstate->m_on_ground = false;

	o_extrabonesprocessing( ecx, edx, a2, a3, a4, a5, a6, a7 );

	animstate->m_on_ground = o_on_ground;
}
