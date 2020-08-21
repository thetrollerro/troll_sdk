#pragma once
#include "../../math/math.hpp"
#include <array>
#include "collideable.hpp"
#include "client_class.hpp"
#include "../structs/animstate.hpp"
#include "../../utilities/netvars/netvars.hpp"
#include "i_client_entity.hpp"
#include "../../utilities/utilities.hpp"
#include "../../interfaces/interfaces.hpp"
#include "../../utilities/csgo.hpp"
#include "../structs/animlayer.hpp"

class c_base_entity;
class c_base_combat_weapon;

enum item_def_idx : short {
	weapon_none = 0,
	weapon_deagle,
	weapon_elite,
	weapon_fiveseven,
	weapon_glock,
	weapon_ak47 = 7,
	weapon_aug,
	weapon_awp,
	weapon_famas,
	weapon_g3sg1,
	weapon_galilar = 13,
	weapon_m249,
	weapon_m4a1 = 16,
	weapon_mac10,
	weapon_p90 = 19,
	weapon_mp5sd = 23,
	weapon_ump45,
	weapon_xm1014,
	weapon_bizon,
	weapon_mag7,
	weapon_negev,
	weapon_sawedoff,
	weapon_tec9,
	weapon_taser,
	weapon_hkp2000,
	weapon_mp7,
	weapon_mp9,
	weapon_nova,
	weapon_p250,
	weapon_scar20 = 38,
	weapon_sg553,
	weapon_ssg08,
	weapon_knifegg,
	weapon_knife,
	weapon_flashbang,
	weapon_hegrenade,
	weapon_smokegrenade,
	weapon_molotov,
	weapon_decoy,
	weapon_incgrenade,
	weapon_c4,
	weapon_healthshot = 57,
	weapon_knife_t = 59,
	weapon_m4a1_silencer,
	weapon_usp_silencer,
	weapon_cz75a = 63,
	weapon_revolver,
	weapon_tagrenade = 68,
	weapon_fists,
	weapon_breachcharge,
	weapon_tablet = 72,
	weapon_melee = 74,
	weapon_axe,
	weapon_hammer,
	weapon_spanner = 78,
	weapon_knife_ghost = 80,
	weapon_firebomb,
	weapon_diversion,
	weapon_frag_grenade,
	weapon_knife_bayonet = 500,
	weapon_knife_ccs = 503,
	weapon_knife_flip = 505,
	weapon_knife_gut,
	weapon_knife_karambit,
	weapon_knife_m9_bayonet,
	weapon_knife_tactical,
	weapon_knife_falchion = 512,
	weapon_knife_survival_bowie = 514,
	weapon_knife_butterfly,
	weapon_knife_push,
	weapon_knife_cord,
	weapon_knife_canis,
	weapon_knife_ursus = 519,
	weapon_knife_gypsy_jackknife,
	weapon_knife_outdoor,
	weapon_knife_stiletto = 522,
	weapon_knife_widowmaker,
	weapon_knife_skeleton = 525,
	glove_studded_bloodhound = 5027,
	glove_t_side = 5028,
	glove_ct_side = 5029,
	glove_sporty = 5030,
	glove_slick = 5031,
	glove_leather_wrap = 5032,
	glove_motorcycle = 5033,
	glove_specialist = 5034,
	glove_hydra = 5035,
	max_itemdefinitionindex
};

enum data_update_type_t {
	data_update_created = 0,
	data_update_datatable_changed,
};

enum cs_c_base_combat_weaponype {
	weapontype_knife = 0,
	weapontype_pistol,
	weapontype_submachinegun,
	weapontype_rifle,
	weapontype_shotgun,
	weapontype_sniper_rifle,
	weapontype_machinegun,
	weapontype_c4,
	weapontype_placeholder,
	weapontype_grenade,
	weapontype_unknown
};

enum client_frame_stage_t {
	frame_undefined = -1,
	frame_start,
	frame_net_update_start,
	frame_net_update_postdataupdate_start,
	frame_net_update_postdataupdate_end,
	frame_net_update_end,
	frame_render_start,
	frame_render_end
};

enum move_type {
	movetype_none = 0,
	movetype_isometric,
	movetype_walk,
	movetype_step,
	movetype_fly,
	movetype_flygravity,
	movetype_vphysics,
	movetype_push,
	movetype_noclip,
	movetype_ladder,
	movetype_observer,
	movetype_custom,
	movetype_last = movetype_custom,
	movetype_max_bits = 4,
	max_movetype
};

enum entity_flags {
	fl_onground = ( 1 << 0 ),
	fl_ducking = ( 1 << 1 ),
	fl_waterjump = ( 1 << 2 ),
	fl_ontrain = ( 1 << 3 ),
	fl_inrain = ( 1 << 4 ),
	fl_frozen = ( 1 << 5 ),
	fl_atcontrols = ( 1 << 6 ),
	fl_client = ( 1 << 7 ),
	fl_fakeclient = ( 1 << 8 ),
	fl_inwater = ( 1 << 9 ),
	fl_fly = ( 1 << 10 ),
	fl_swim = ( 1 << 11 ),
	fl_conveyor = ( 1 << 12 ),
	fl_npc = ( 1 << 13 ),
	fl_godmode = ( 1 << 14 ),
	fl_notarget = ( 1 << 15 ),
	fl_aimtarget = ( 1 << 16 ),
	fl_partialground = ( 1 << 17 ),
	fl_staticprop = ( 1 << 18 ),
	fl_graphed = ( 1 << 19 ),
	fl_grenade = ( 1 << 20 ),
	fl_stepmovement = ( 1 << 21 ),
	fl_donttouch = ( 1 << 22 ),
	fl_basevelocity = ( 1 << 23 ),
	fl_worldbrush = ( 1 << 24 ),
	fl_object = ( 1 << 25 ),
	fl_killme = ( 1 << 26 ),
	fl_onfire = ( 1 << 27 ),
	fl_dissolving = ( 1 << 28 ),
	fl_transragdoll = ( 1 << 29 ),
	fl_unblockable_by_player = ( 1 << 30 )
};
inline c_base_entity* g_local;

class c_base_entity : public i_client_entity {
private:
	template <typename T>
	T& read( uintptr_t offset ) {
		return *reinterpret_cast< T* >( reinterpret_cast< uintptr_t >( this ) + offset );
	}

	template <typename T>
	void write( uintptr_t offset, T data ) {
		*reinterpret_cast< T* >( reinterpret_cast< uintptr_t >( this ) + offset ) = data;
	}

public:
	/* DT_BasePlayer */
	NETVAR( "DT_BasePlayer->m_vecVelocity[0]", m_vecVelocity, vec3_t );
	NETVAR( "DT_BasePlayer->m_flMaxspeed", m_flMaxspeed, float );
	NETVAR( "DT_BasePlayer->m_hObserverTarget", m_hObserverTarget, unsigned long );
	NETVAR( "DT_BasePlayer->m_nHitboxSet", m_nHitboxSet, int );
	NETVAR( "DT_BasePlayer->m_hViewModel[0]", m_hViewModel, int );
	NETVAR( "DT_BasePlayer->m_aimPunchAngle", m_aimPunchAngle, vec3_t );
	NETVAR( "DT_BasePlayer->m_viewPunchAngle", m_viewPunchAngle, vec3_t );
	NETVAR( "DT_BasePlayer->m_flDuckSpeed", m_flDuckSpeed, float );

	/* DT_BaseEntity */
	NETVAR( "DT_BaseEntity->m_hOwnerEntity", m_hOwnerEntity, unsigned long );
	NETVAR( "DT_BaseEntity->m_flShadowCastDistance", m_flShadowCastDistance, float );
	NETVAR( "DT_BasePlayer->m_vecOrigin", m_vecOrigin, vec3_t );
	NETVAR( "DT_BasePlayer->m_vecViewOffset[0]", m_vecViewOffset, vec3_t );
	NETVAR( "DT_BaseEntity->m_bSpotted", m_bSpotted, bool );
	NETVAR( "DT_BaseEntity->m_nModelIndex", m_nModelIndex, int32_t );
	NETVAR_OFFSET( "DT_BaseEntity->m_nRenderMode", 0x1, m_nMoveType, int );

	/* DT_CSPlayer */
	NETVAR( "DT_CSPlayer->m_nSurvivalTeam", m_nSurvivalTeam, int );
	NETVAR( "DT_CSPlayer->m_flHealthShotBoostExpirationTime", m_flHealthShotBoostExpirationTime, float );
	NETVAR( "DT_CSPlayer->m_fFlags", m_fFlags, int );
	NETVAR( "DT_CSPlayer->m_iTeamNum", m_iTeamNum, int );
	NETVAR( "DT_CSPlayer->m_flSimulationTime", m_flSimulationTime, float );
	NETVAR( "DT_CSPlayer->m_bHasDefuser", m_bHasDefuser, bool );
	NETVAR( "DT_CSPlayer->m_bGunGameImmunity", m_bGunGameImmunity, bool );
	NETVAR( "DT_CSPlayer->m_iShotsFired", m_iShotsFired, int );
	NETVAR( "DT_CSPlayer->m_angEyeAngles[0]", m_angEyeAngles, vec3_t );
	NETVAR( "DT_CSPlayer->m_ArmorValue", m_ArmorValue, int );
	NETVAR( "DT_CSPlayer->m_bHasHelmet", m_bHasHelmet, bool );
	NETVAR( "DT_CSPlayer->m_bIsScoped", m_bIsScoped, bool );
	NETVAR( "DT_CSPlayer->m_bIsDefusing", m_bIsDefusing, bool );
	NETVAR( "DT_CSPlayer->m_iAccount", m_iAccount, int );
	NETVAR( "DT_CSPlayer->m_flLowerBodyYawTarget", m_flLowerBodyYawTarget, float );
	NETVAR( "DT_CSPlayer->m_flNextAttack", m_flNextAttack, float );
	NETVAR( "DT_CSPlayer->m_flFlashDuration", m_flFlashDuration, float );
	NETVAR( "DT_CSPlayer->m_flFlashMaxAlpha", m_flFlashMaxAlpha, float );
	NETVAR( "DT_CSPlayer->m_bHasNightVision", m_bHasNightVision, float );
	NETVAR( "DT_CSPlayer->m_bNightVisionOn", m_bNightVisionOn, float );
	NETVAR( "DT_CSPlayer->m_iHealth", m_iHealth, int );
	NETVAR( "DT_CSPlayer->m_lifeState", m_lifeState, int );
	NETVAR( "DT_CSPlayer->m_flDuckAmount", m_flDuckAmount, float );
	NETVAR( "DT_CSPlayer->m_bHasHeavyArmor", m_bHasHeavyArmor, bool );
	NETVAR( "DT_CSPlayer->m_nTickBase", m_nTickBase, int );
	OFFSET( vec3_t, m_vecAbsVelocity, 0x94 );
	NETVAR_PTR( "DT_CSPlayer->m_hMyWeapons", m_hMyWeapons, UINT );
	NETVAR_PTR( "DT_CSPlayer->m_hMyWearables", m_hMyWearables, UINT );
	NETVAR_OFFSET( "DT_CSPlayer->m_flSimulationTime", 0x4, m_flOldSimulationTime, float );

	/* DT_SmokeGrenadeProjectile */
	NETVAR( "DT_SmokeGrenadeProjectile->m_nSmokeEffectTickBegin", m_nSmokeEffectTickBegin, int );

	/* DT_BaseAnimating */
	NETVAR( "DT_BaseAnimating->m_bClientSideAnimation", m_bClientSideAnimation, bool );

	/* offsets */
	OFFSET( int, m_iEFlags, 0xE8 );
	OFFSET( float, m_flSpawnTime, 0xA370 );
	OFFSET( uint32_t, get_most_recent_model_bone_counter, 0x2690 );
	OFFSET( float, get_last_bone_setup_time, 0x2924 );
	OFFSET( vec3_t, tp_angles, 0x31D8 );
	OFFSET_PTR( animstate_t, get_animstate, 0x3914 );
	OFFSET_PTR( animlayer_t, get_animoverlays, 0x2980 );

	bool is_player( ) {
		using o_fn = bool( __thiscall* )( c_base_entity* );
		return utilities::call_virtual<o_fn>( this, 157 )( this );
	}

	bool is_weapon( ) {
		using o_fn = bool( __thiscall* )( c_base_entity* );
		return utilities::call_virtual<o_fn>( this, 166 )( this );
	}

	void set_model_index( int index ) {
		using o_fn = void( __thiscall* )( void*, int );
		return utilities::call_virtual<o_fn>( this, 75 )( this, index );
	}

	vec3_t& abs_origin( ) {
		using o_fn = vec3_t & ( __thiscall* )( void* );
		return utilities::call_virtual<o_fn>( this, 10 )( this );
	}

	vec3_t& abs_angles( ) {
		using o_fn = vec3_t & ( __thiscall* )( void* );
		return utilities::call_virtual<o_fn>( this, 11 )( this );
	}

	c_base_combat_weapon* get_active_weapon( ) {
		auto active_weapon = read<uintptr_t>( netvars::get_offset( "DT_CSPlayer->m_hActiveWeapon" ) ) & 0xFFF;
		return reinterpret_cast< c_base_combat_weapon* >( interfaces::entity_list->get_client_entity( active_weapon ) );
	}
	void update_clientside_animation( ) {
		using o_fn = void( __thiscall* )( void* );
		static auto update_clientside_animation = ( o_fn ) utilities::find_sig_ida( "client.dll", "55 8B EC 51 56 8B F1 80 BE ? ? ? ? ? 74 36" );
		if ( !update_clientside_animation ) return;
		update_clientside_animation( this );
	}
	std::array<float, 24>& m_flPoseParameter( ) {
		static int _m_flPoseParameter = netvars::get_offset( "DT_BaseAnimating->m_flPoseParameter" );
		return *( std::array<float, 24>* )( uintptr_t( this ) + _m_flPoseParameter );
	}
	matrix_t get_bone_matrix( int id ) {
		matrix_t matrix;

		auto offset = *reinterpret_cast< uintptr_t* >( uintptr_t( this ) + 0x26A8 );
		if ( offset )
			matrix = *reinterpret_cast< matrix_t* >( offset + 0x30 * id );

		return matrix;
	}
	vec3_t get_bone_pos( int i ) {
		matrix_t matrix[ 128 ];

		if ( this->setup_bones( matrix, 128, 0x00000100, GetTickCount64( ) ) ) {
			return vec3_t( matrix[ i ][ 0 ][ 3 ], matrix[ i ][ 1 ][ 3 ], matrix[ i ][ 2 ][ 3 ] );
		}

		return vec3_t( 0, 0, 0 );
	}
	void create_anim_state( animstate_t* state )
	{
		using create_anim_state_t = void( __thiscall* ) ( animstate_t*, c_base_entity* );
		static auto create_anim_state = reinterpret_cast< create_anim_state_t > ( utilities::find_sig_ida( "client.dll", "55 8B EC 56 8B F1 B9 ? ? ? ? C7 46" ) );

		if ( !create_anim_state )
			return;

		if ( !state )
			return;

		create_anim_state( state, this );
	}
	float max_desync_delta( ) {
		auto animstate = uintptr_t( this->get_animstate( ) );

		float duckammount = *( float* ) ( animstate + 0xA4 );
		float speedfraction = std::fmax( 0, std::fmin( *reinterpret_cast< float* >( animstate + 0xF8 ), 1 ) );

		float speedfactor = std::fmax( 0, std::fmin( 1, *reinterpret_cast< float* > ( animstate + 0xFC ) ) );

		float unk1 = ( ( *reinterpret_cast< float* > ( animstate + 0x11C ) * -0.30000001 ) - 0.19999999 ) * speedfraction;
		float unk2 = unk1 + 1.f;
		float unk3;

		if ( duckammount > 0 ) {

			unk2 += ( ( duckammount * speedfactor ) * ( 0.5f - unk2 ) );

		}

		unk3 = *( float* ) ( animstate + 0x334 ) * unk2;

		return unk3;
	}
	vec3_t get_hitbox_pos( int hitbox_id, matrix_t* bone_matrix )
	{
		auto studio_model = interfaces::model_info->get_studio_model( get_model( ) );
		if ( studio_model ) {
			auto hitbox = studio_model->hitbox_set( 0 )->hitbox( hitbox_id );
			if ( hitbox ) {
				auto
					min = vec3_t {},
					max = vec3_t {};

				math::vector_transform( hitbox->mins, bone_matrix[ hitbox->bone ], min );
				math::vector_transform( hitbox->maxs, bone_matrix[ hitbox->bone ], max );

				return ( min + max ) / 2.0f;
			}
		}
		return vec3_t {};
	}
	vec3_t get_eye_pos( ) {
		return m_vecOrigin( ) + m_vecViewOffset( );
	}
	bool can_see_player_pos( c_base_entity* player, vec3_t& pos ) {
		trace_t tr;
		ray_t ray;
		trace_filter filter;
		filter.skip = this;

		filter.skip = this;

		ray.initialize( get_eye_pos( ), pos );
		interfaces::trace_ray->trace_ray( ray, mask_shot | contents_grate, &filter, &tr );

		return tr.entity == player || tr.fraction > 0.97f;
	}
	void invalidate_bone_cache( )
	{
		static auto model_bone_counter = utilities::find_sig_ida( "client.dll", "80 3D ? ? ? ? ? 74 16 A1 ? ? ? ? 48 C7 81" ) + 10;
		*( uint32_t* ) ( ( uintptr_t ) ( this ) + 0x2924 ) = -FLT_MAX; // m_flLastBoneSetupTime = -FLT_MAX
		*( uint32_t* ) ( ( uintptr_t ) ( this ) + 0x2690 ) = **( unsigned long** ) model_bone_counter - 1; // m_iMostRecentModelBoneCounter = g_iModelBoneCounter - 1;
	}
	bool is_alive( ) {
		return m_iHealth( ) > 0;
	}
	int get_choked_packets( ) {
		static int last_ticks[ 65 ];
		auto ticks = TIME_TO_TICKS( this->m_flSimulationTime( ) - this->m_flOldSimulationTime( ) );
		if ( ticks == 0 && last_ticks[ this->ent_index( ) ] > 0 ) {
			return last_ticks[ this->ent_index( ) ] - 1;
		}
		else {
			last_ticks[ this->ent_index( ) ] = ticks;
			return ticks;
		}
	}
	player_info_t get_player_info( )
	{
		player_info_t pinfo;
		interfaces::engine->get_player_info( ent_index( ), &pinfo );
		return pinfo;
	}
	void set_abs_angles( vec3_t angles ) {
		using o_fn = void( __thiscall* )( void*, const vec3_t& );
		static o_fn set_angles_fn = ( o_fn ) utilities::find_sig_ida( "client.dll", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1" );
		set_angles_fn( this, angles );
	}
	void set_abs_origin( vec3_t position ) {
		using o_fn = void( __thiscall* )( void*, const vec3_t& );
		static o_fn set_position_fn = ( o_fn ) utilities::find_sig_ida( "client.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8" );
		set_position_fn( this, position );
	}
	bool is_enemy( ) {
		return ( this->m_iTeamNum( ) != g_local->m_iTeamNum( ) );
	}
	bool is_valid_target( ) {
		auto class_id = this->get_client_class( )->class_id;
		if ( !this ) return false;
		if ( !this->is_enemy( ) ) return false;
		if ( this->m_iHealth( ) <= 0 ) return false;
		if ( class_id != class_id_cs_player ) return false;
		if ( this->m_vecOrigin( ) == vec3_t( 0, 0, 0 ) ) return false;
		if ( this->m_bGunGameImmunity( ) ) return false;
		if ( this->is_dormant( ) ) return false;

		return true;
	}
};

class c_base_combat_weapon : public c_base_entity {
public:
	/* DT_BaseCombatWeapon */
	NETVAR( "DT_BaseCombatWeapon->m_flNextPrimaryAttack", m_flNextPrimaryAttack, float );
	NETVAR( "DT_BaseCombatWeapon->m_flNextSecondaryAttack", m_flNextSecondaryAttack, float );
	NETVAR( "DT_BaseCombatWeapon->m_iClip1", m_iClip1, int );
	NETVAR( "DT_BaseCombatWeapon->m_iClip2", m_iClip2, int );
	NETVAR( "DT_BaseCombatWeapon->m_iPrimaryReserveAmmoCount", m_iPrimaryReserveAmmoCount, int );
	NETVAR( "DT_BaseCombatWeapon->m_iViewModelIndex", m_iViewModelIndex, int32_t );
	NETVAR( "DT_BaseCombatWeapon->m_iEntityQuality", m_iEntityQuality, int );

	/* DT_BaseAttributableItem */
	NETVAR( "DT_BaseAttributableItem->m_iItemDefinitionIndex", m_iItemDefinitionIndex, short );
	NETVAR( "DT_BaseAttributableItem->m_OriginalOwnerXuidLow", m_OriginalOwnerXuidLow, int );
	NETVAR( "DT_BaseAttributableItem->m_OriginalOwnerXuidHigh", m_OriginalOwnerXuidHigh, int );
	NETVAR( "DT_BaseAttributableItem->m_nFallbackStatTrak", m_nFallbackStatTrak, int );
	NETVAR( "DT_BaseAttributableItem->m_nFallbackPaintKit", m_nFallbackPaintKit, int );
	NETVAR( "DT_BaseAttributableItem->m_iItemIDHigh", m_iItemIDHigh, int );
	NETVAR( "DT_BaseAttributableItem->m_nFallbackSeed", m_nFallbackSeed, int );
	NETVAR( "DT_BaseAttributableItem->m_flFallbackWear", m_flFallbackWear, float );

	/* DT_WeaponCSBase */
	NETVAR( "DT_WeaponCSBase->m_flRecoilIndex", m_flRecoilIndex, float );
	NETVAR( "DT_WeaponCSBase->m_bPinPulled", m_bPinPulled, bool );
	NETVAR( "DT_WeaponCSBase->m_fLastShotTime", m_fLastShotTime, float );

	/* DT_WeaponCSBaseGun */
	NETVAR( "DT_WeaponCSBaseGun->m_zoomLevel", m_zoomLevel, float );

	/* DT_BaseCSGrenade */
	NETVAR( "DT_BaseCSGrenade->m_fThrowTime", m_fThrowTime, float );

	/* DT_ScriptCreatedItem */
	NETVAR( "DT_ScriptCreatedItem->m_bInitialized", m_bInitialized, bool );
	NETVAR( "DT_ScriptCreatedItem->m_iEntityLevel", m_iEntityLevel, int );
	NETVAR( "DT_ScriptCreatedItem->m_iAccountID", m_iAccountID, int );
	NETVAR( "DT_ScriptCreatedItem->m_iItemIDLow", m_iItemIDLow, int );

	float fire_rate( ) {
		if ( !g_local || !g_local->is_alive( ) || !this || this->is_knife( ) || this->is_nade( ) ) return 0.f;

		std::string weapon_name = this->get_name( );

		if ( weapon_name == "weapon_glock" )
			return 0.15f;
		else if ( weapon_name == "weapon_hkp2000" )
			return 0.169f;
		else if ( weapon_name == "weapon_p250" )//the cz and p250 have the same name idky same with other guns
			return 0.15f;
		else if ( weapon_name == "weapon_tec9" )
			return 0.12f;
		else if ( weapon_name == "weapon_elite" )
			return 0.12f;
		else if ( weapon_name == "weapon_fiveseven" )
			return 0.15f;
		else if ( weapon_name == "weapon_deagle" )
			return 0.224f;
		else if ( weapon_name == "weapon_nova" )
			return 0.882f;
		else if ( weapon_name == "weapon_sawedoff" )
			return 0.845f;
		else if ( weapon_name == "weapon_mag7" )
			return 0.845f;
		else if ( weapon_name == "weapon_xm1014" )
			return 0.35f;
		else if ( weapon_name == "weapon_mac10" )
			return 0.075f;
		else if ( weapon_name == "weapon_ump45" )
			return 0.089f;
		else if ( weapon_name == "weapon_mp9" )
			return 0.070f;
		else if ( weapon_name == "weapon_bizon" )
			return 0.08f;
		else if ( weapon_name == "weapon_mp7" )
			return 0.08f;
		else if ( weapon_name == "weapon_p90" )
			return 0.070f;
		else if ( weapon_name == "weapon_galilar" )
			return 0.089f;
		else if ( weapon_name == "weapon_ak47" )
			return 0.1f;
		else if ( weapon_name == "weapon_sg556" )
			return 0.089f;
		else if ( weapon_name == "weapon_m4a1" )
			return 0.089f;
		else if ( weapon_name == "weapon_aug" )
			return 0.089f;
		else if ( weapon_name == "weapon_m249" )
			return 0.08f;
		else if ( weapon_name == "weapon_negev" )
			return 0.0008f;
		else if ( weapon_name == "weapon_ssg08" )
			return 1.25f;
		else if ( weapon_name == "weapon_awp" )
			return 1.463f;
		else if ( weapon_name == "weapon_g3sg1" )
			return 0.25f;
		else if ( weapon_name == "weapon_scar20" )
			return 0.25f;
		else if ( weapon_name == "weapon_mp5sd" )
			return 0.08f;
		else
			return .0f;
	}

	std::string weapon_name( ) {
		if ( !this || !m_iItemDefinitionIndex( ) )
			return "invalid";

		int weap_id = this->m_iItemDefinitionIndex( );
		switch ( weap_id ) {
		case weapon_deagle:
			return "deagle";
		case weapon_elite:
			return "elite";
		case weapon_fiveseven:
			return "fiveseven";
		case weapon_glock:
			return "glock";
		case weapon_ak47:
			return "ak47";
		case weapon_aug:
			return "aug";
		case weapon_awp:
			return "awp";
		case weapon_famas:
			return "famas";
		case weapon_g3sg1:
			return "g3sg1";
		case weapon_galilar:
			return "galilar";
		case weapon_m249:
			return "m249";
		case weapon_m4a1:
			return "m4a4";
		case weapon_mac10:
			return "mac10";
		case weapon_p90:
			return "p90";
		case weapon_ump45:
			return "ump45";
		case weapon_xm1014:
			return "xm1014";
		case weapon_bizon:
			return "bizon";
		case weapon_mag7:
			return "mag7";
		case weapon_negev:
			return "negev";
		case weapon_sawedoff:
			return "sawedoff";
		case weapon_tec9:
			return "tec9";
		case weapon_hkp2000:
			return "hkp2000";
		case weapon_mp7:
			return "mp7";
		case weapon_mp9:
			return "mp9";
		case weapon_nova:
			return "nova";
		case weapon_p250:
			return "p250";
		case weapon_scar20:
			return "scar20";
		case weapon_sg553:
			return "sg553";
		case weapon_ssg08:
			return "ssg08";
		case weapon_m4a1_silencer:
			return "m4a1_silencer";
		case weapon_usp_silencer:
			return "usp_silencer";
		case weapon_cz75a:
			return "cz75a";
		case weapon_revolver:
			return "revolver";
		case weapon_knife_bayonet:
			return "bayonet";
		case weapon_knife_ccs:
			return "knife_ccs";
		case weapon_knife_flip:
			return "knife_flip";
		case weapon_knife_gut:
			return "knife_gut";
		case weapon_knife_karambit:
			return "knife_karambit";
		case weapon_knife_m9_bayonet:
			return "knife_m9_bayonet";
		case weapon_knife_tactical:
			return "knife_tactical";
		case weapon_knife_falchion:
			return "knife_falchion";
		case weapon_knife_survival_bowie:
			return "knife_survival_bowie";
		case weapon_knife_butterfly:
			return "knife_butterfly";
		case weapon_knife_push:
			return "knife_push";
		case weapon_knife_cord:
			return "knife_cord";
		case weapon_knife_canis:
			return "knife_canis";
		case weapon_knife_ursus:
			return "knife_ursus";
		case weapon_knife_gypsy_jackknife:
			return "knife_gypsy_jackknife";
		case weapon_knife_stiletto:
			return "knife_stiletto";
		case weapon_knife_outdoor:
			return "knife_outdoor";
		case weapon_knife_widowmaker:
			return "knife_widowmaker";
		case weapon_knife_skeleton:
			return "knife_skeleton";
		default:
			return "";
		}
	}

	float inaccuracy( ) {
		using o_fn = float( __thiscall* )( void* );
		return utilities::call_virtual<o_fn>( this, 482 )( this );
	}

	float get_spread( ) {
		using o_fn = float( __thiscall* )( void* );
		return utilities::call_virtual<o_fn>( this, 452 )( this );
	}

	void update_accuracy_penalty( ) {
		using o_fn = void( __thiscall* )( void* );
		return utilities::call_virtual<o_fn>( this, 483 )( this );
	}

	weapon_info_t* get_cs_weapon_data( ) {
		using o_fn = weapon_info_t * ( __thiscall* )( void* );
		return utilities::call_virtual< o_fn >( this, 460 )( this );
	}

	bool is_knife( ) {
		return get_cs_weapon_data( )->weapon_type == weapontype_knife;
	}

	bool is_nade( ) {
		return get_cs_weapon_data( )->weapon_type == weapontype_grenade;
	}

	bool is_zeus( ) {
		return m_iItemDefinitionIndex( ) == weapon_taser;
	}

	bool is_pistol( ) {
		return get_cs_weapon_data( )->weapon_type == weapontype_pistol;
	}

	bool is_rifle( ) {
		return get_cs_weapon_data( )->weapon_type == weapontype_rifle;
	}

	bool is_sniper( ) {
		return get_cs_weapon_data( )->weapon_type == weapontype_sniper_rifle;
	}

	bool is_smg( ) {
		return get_cs_weapon_data( )->weapon_type == weapontype_submachinegun;
	}

	bool is_heavy( ) {
		return get_cs_weapon_data( )->weapon_type == weapontype_machinegun;
	}

	std::string get_name( ) {
		return std::string( this->get_cs_weapon_data( )->weapon_name );
	}
};

class c_base_view_model : public c_base_entity {
public:
	/* DT_BaseViewModel */
	NETVAR( "DT_BaseViewModel->m_nModelIndex", m_nModelIndex, int );
	NETVAR( "DT_BaseViewModel->m_nViewModelIndex", m_nViewModelIndex, int );
	NETVAR( "DT_BaseViewModel->m_hWeapon", m_hWeapon, int );
	NETVAR( "DT_BaseViewModel->m_hOwner", m_hOwner, int );

	inline int get_model_index( ) {

		return *( int* ) ( ( DWORD ) this + 0x258 );
	}
};


class c_cs_bomb {
public:
	NETVAR( "DT_PlantedC4->m_flC4Blow", m_flC4Blow, float );
	NETVAR( "DT_PlantedC4->m_flDefuseCountDown", m_flDefuseCountDown, float );
	NETVAR( "DT_PlantedC4->m_hBombDefuser", m_hBombDefuser, int );
	NETVAR( "DT_PlantedC4->m_bBombDefused", m_bBombDefused, bool );
};
