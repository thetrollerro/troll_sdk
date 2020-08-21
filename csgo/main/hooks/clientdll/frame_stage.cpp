#include "../hooks.hpp"

std::vector<const char*> smoke_materials =
{
	"particle/beam_smoke_01",
	"particle/particle_smokegrenade",
	"particle/particle_smokegrenade1",
	"particle/particle_smokegrenade2",
	"particle/particle_smokegrenade3",
	"particle/particle_smokegrenade_sc",
	"particle/smoke1/smoke1",
	"particle/smoke1/smoke1_ash",
	"particle/smoke1/smoke1_nearcull",
	"particle/smoke1/smoke1_nearcull2",
	"particle/smoke1/smoke1_snow",
	"particle/smokesprites_0001",
	"particle/smokestack",
	"particle/vistasmokev1/vistasmokev1",
	"particle/vistasmokev1/vistasmokev1_emods",
	"particle/vistasmokev1/vistasmokev1_emods_impactdust",
	"particle/vistasmokev1/vistasmokev1_fire",
	"particle/vistasmokev1/vistasmokev1_nearcull",
	"particle/vistasmokev1/vistasmokev1_nearcull_fog",
	"particle/vistasmokev1/vistasmokev1_nearcull_nodepth",
	"particle/vistasmokev1/vistasmokev1_smokegrenade",
	"particle/vistasmokev1/vistasmokev4_emods_nocull",
	"particle/vistasmokev1/vistasmokev4_nearcull",
	"particle/vistasmokev1/vistasmokev4_nocull"
};

void __fastcall hooks::frame_stage::hook( void* ecx, void* edx, int stage ) {
	if ( !interfaces::engine->is_connected( ) || !interfaces::engine->is_in_game( ) || !g_local || !g_local->is_alive( ) ) {
		o_framestage( interfaces::client, edx, stage );
		return;
	}

	switch ( stage )
	{

	case frame_start:

		break;

	case frame_net_update_start:
		
		break;

	case frame_net_update_postdataupdate_start:

		break;

	case frame_net_update_postdataupdate_end:

		break;

	case frame_net_update_end:

		break;

	case frame_render_start:

		/* pvs fix */
		for ( int i = 1; i < 65; i++ ) {
			auto e = ( c_base_entity* ) interfaces::entity_list->get_client_entity( i );
			if ( !e || !e->is_player( ) || e == g_local ) continue;

			*( int* ) ( ( uintptr_t ) e + 0xA30 ) = interfaces::globals->frame_count;
			*( int* ) ( ( uintptr_t ) e + 0xA28 ) = 0;
		}

		break;

	case frame_render_end:

		break;

	}

	o_framestage( interfaces::client, edx, stage );
}