#include "../hooks.hpp"

bool __fastcall hooks::create_move::hook( void* ecx, void* edx, float input_sample_frametime, c_usercmd* cmd ) {
	o_createmove( interfaces::clientmode, edx, input_sample_frametime, cmd );

	if ( !cmd || !cmd->command_number ) return o_createmove( interfaces::clientmode, edx, input_sample_frametime, cmd );

	/* get globals */
	g::cmd = cmd;
	g_local = ( c_base_entity* ) interfaces::entity_list->get_client_entity( interfaces::engine->get_local_player( ) );
	g::send_packet = true;

	/* get send_packet stuff */
	uintptr_t* framePtr; __asm mov framePtr, ebp;

	if ( !interfaces::engine->is_in_game( ) || !g_local || !g_local->is_alive( ) ) return o_createmove( interfaces::clientmode, edx, input_sample_frametime, cmd );

	/* fix attack stuff */ {
		auto weapon = g_local->get_active_weapon( );
		if ( weapon ) {
			float flServerTime = g_local->m_nTickBase( ) * interfaces::globals->interval_per_tick;
			bool can_shoot = ( weapon->m_flNextPrimaryAttack( ) <= flServerTime );
			if ( ( !can_shoot && !weapon->is_nade( ) ) || menu::opened ) {
				cmd->buttons &= ~in_attack;
			}
		}
	}

	/* prediction system related */ {
		prediction::start( cmd );

		prediction::end( );
	}

	/* anti-untrusted */ {
		cmd->viewangles.clamp( );
	}

	/* get global angles */ {
		if ( g::send_packet ) {
			g::fake_angle = cmd->viewangles;
		}
		else {
			g::real_angle = cmd->viewangles;
		}
	}

	*( bool* ) ( *framePtr - 0x1C ) = g::send_packet;
	return false;
}