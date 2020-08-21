#pragma once
#include "../main.hpp"
#include "../features/features.hpp"
#include "../menu/menu.hpp"

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace hooks {
	bool initialize( );
	void release( );

	inline unsigned int get_virtual( void* _class, unsigned int index ) { return static_cast< unsigned int >( ( *reinterpret_cast< int** >( _class ) )[ index ] ); }
	/* bsp_tree_query */
	namespace list_leaves_in_box {
		/* target stuff */
		const int index = 6;

		/* hook stuff */
		using fn = int( __fastcall* )( void*, void*, const vec3_t&, const vec3_t&, unsigned short*, int );
		int __fastcall hook( void* ecx, void* edx, vec3_t& mins, vec3_t& maxs, unsigned short* list, int list_max );
	}



	/* clientdll */
	namespace frame_stage {
		/* target stuff */
		const int index = 37;

		/* hook stuff */
		using fn = void( __fastcall* )( void*, void*, int );
		void __fastcall hook( void* ecx, void* edx, int stage );
	}



	/* clientmode */
	namespace create_move {
		/* target stuff */
		const int index = 24;

		/* hook stuff */
		using fn = bool( __fastcall* )( void*, void*, float, c_usercmd* );
		bool __fastcall hook( void* ecx, void* edx, float input_sample_frametime, c_usercmd* cmd );
	};

	namespace get_viewmodel_fov {
		/* target stuff */
		const int index = 35;

		/* hook stuff */
		using fn = float( __fastcall* )( void*, void* );
		float __fastcall hook( void* ecx, void* edx );
	}

	namespace override_view {
		/* target stuff */
		const int index = 18;

		/* hook stuff */
		using fn = void( __fastcall* )( void*, void*, view_setup_t* );
		void __fastcall hook( void* ecx, void* edx, view_setup_t* view );
	}



	/* directx */
	namespace end_scene {
		/* target stuff */
		const int index = 42;

		/* hook stuff */
		using fn = long( __stdcall* )( IDirect3DDevice9* );
		long __stdcall hook( IDirect3DDevice9* dev );
	}

	namespace present {
		/* target stuff */
		const int index = 17;

		/* hook stuff */
		using fn = long( __stdcall* )( IDirect3DDevice9*, RECT*, RECT*, HWND, RGNDATA* );
		long __stdcall hook( IDirect3DDevice9* dev, RECT* source_rect, RECT* dust_rect, HWND dest_window_override, RGNDATA* dirty_region );
	}

	namespace reset {
		/* target stuff */
		const int index = 16;

		/* hook stuff */
		using fn = long( __stdcall* )( IDirect3DDevice9*, D3DPRESENT_PARAMETERS* );
		long __stdcall hook( IDirect3DDevice9* dev, D3DPRESENT_PARAMETERS* params );
	}



	/* engine */
	namespace fire_game_event {
		/* target stuff */
		const int index = 59;

		/* hook stuff */
		using fn = void( __fastcall* )( void*, void* );
		void __fastcall hook( void* ecx, void* edx );
	}

	namespace get_screen_aspect_ratio {
		/* target stuff */
		const int index = 101;

		/* hook stuff */
		using fn = float( __fastcall* )( void*, void*, int, int );
		float __fastcall hook( void* ecx, void* edx, int x, int y );
	}

	namespace is_hltv {
		/* target stuff */
		const int index = 93;

		/* hook stuff */
		using fn = bool( __fastcall* )( uintptr_t, uintptr_t );
		bool __fastcall hook( uintptr_t ecx, uintptr_t edx );
	}



	/* game */
	class events : public i_game_event_listener {
	public:
		void fire_game_event( i_game_event* event );
		int get_event_debug_id = 42;

		void initialize( ) {
			interfaces::event_manager->add_listener( this, "player_hurt", false );
			interfaces::event_manager->add_listener( this, "player_death", false );
			interfaces::event_manager->add_listener( this, "bullet_impact", false );
			interfaces::event_manager->add_listener( this, "weapon_fire", false );
			interfaces::event_manager->add_listener( this, "round_start", false );
			interfaces::event_manager->add_listener( this, "item_purchase", false );
		}

		void restore( ) {
			interfaces::event_manager->remove_listener( this );
		}
	};
	inline events event_mgr;

	namespace sv_cheats_bool {
		/* backup */
		const int index = 13; // interfaces::cvar->find_var( "sv_cheats" )

		using fn = bool( __fastcall* )( void*, void* );
		bool __fastcall hook( void* ecx, void* edx );
	}

	long wndproc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam );



	/* modelrender */
	namespace draw_model_exec {
		/* target stuff */
		const int index = 21;

		/* hook stuff */
		using fn = void( __fastcall* )( void*, int, void*, const draw_model_state_t&, const model_render_info_t&, matrix_t* );
		void __fastcall hook( void* ecx, int edx, void* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* custom_bone_to_world = nullptr );
	}



	/* players hook */
	namespace do_extra_bones_processing {
		using fn = void( __fastcall* )( void*, void*, int, int, int, int, int, int );
		void __fastcall hook( void* ecx, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 );
	}

	namespace get_eye_ang {
		using fn = vec3_t * ( __fastcall* )( void*, void* );
		vec3_t* __fastcall hook( void* ecx, void* edx );
	}

	namespace setup_bones {
		using fn = bool( __fastcall* )( void*, void*, matrix_t*, int, int, float );
		bool __fastcall hook( void* ecx, void* edx, matrix_t* bone_to_world_out, int max_bones, int bone_mask, float curtime );
	}

	namespace update_clientside_animation {
		using fn = void( __fastcall* )( void*, void* );
		void __fastcall hook( void* ecx, void* edx );
	}



	/* surface */
	namespace lock_cursor {
		/* target stuff */
		const int index = 67;

		/* hook stuff */
		using fn = void( __fastcall* )( void*, void* );
		void __fastcall hook( void* ecx, void* edx );
	}

	void dx_things( IDirect3DDevice9* dev );

	/* wndproc vars */
	inline bool pressed_keys[ 256 ];
	inline HWND csgo_window = nullptr;
	inline WNDPROC orig_wnd_proc = nullptr;
}

/* originals */
inline hooks::list_leaves_in_box::fn o_listleavesinbox;
inline hooks::frame_stage::fn o_framestage;
inline hooks::create_move::fn o_createmove;
inline hooks::get_viewmodel_fov::fn o_viewmdlfov;
inline hooks::override_view::fn o_overrideview;
inline hooks::end_scene::fn o_endscene;
inline hooks::present::fn o_present;
inline hooks::reset::fn o_reset;
inline hooks::fire_game_event::fn o_fireevent;
inline hooks::get_screen_aspect_ratio::fn o_aspectratio;
inline hooks::is_hltv::fn o_ishltv;
inline hooks::sv_cheats_bool::fn o_svcheatsbool;
inline hooks::draw_model_exec::fn o_drawmodelexec;
inline hooks::do_extra_bones_processing::fn o_extrabonesprocessing;
inline hooks::get_eye_ang::fn o_eyeang;
inline hooks::setup_bones::fn o_setupbones;
inline hooks::update_clientside_animation::fn o_updateclientanim;
inline hooks::lock_cursor::fn o_lockcursor;
