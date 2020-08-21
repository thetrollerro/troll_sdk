#include "hooks.hpp"


bool hooks::initialize( ) {

	/* get window handle */
	while ( !( csgo_window = FindWindowA( "Valve001", nullptr ) ) ) {
		using namespace std::literals::chrono_literals;
		std::this_thread::sleep_for( 50ms );
	}

	/* create fonts */
	render::create_fonts( );

	/* hook wnd_proc */
	orig_wnd_proc = reinterpret_cast< WNDPROC >( SetWindowLongPtr( csgo_window, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( hooks::wndproc ) ) );

	/* targets */
	const auto list_leaves_in_box_target = ( void* ) get_virtual( interfaces::engine->get_bsp_tree_query( ), list_leaves_in_box::index );
	const auto frame_stage_target = ( void* ) utilities::find_sig_ida( "client.dll", "55 8B EC 8B 0D ? ? ? ? 8B 01 8B 80 74 01 00 00 FF D0 A2" );
	const auto create_move_target = ( void* ) utilities::find_sig_ida( "client.dll", "55 8B EC 8B 0D ? ? ? ? 85 C9 75 06 B0" );
	const auto get_viewmodel_fov_target = ( void* ) get_virtual( interfaces::clientmode, get_viewmodel_fov::index );
	const auto override_view_target = ( void* ) utilities::find_sig_ida( "client.dll", "55 8B EC 83 E4 F8 83 EC 58 56 57 8B 3D ? ? ? ? 85 FF" );
	const auto end_scene_target = ( void* ) get_virtual( interfaces::directx, end_scene::index );
	const auto present_target = ( void* ) get_virtual( interfaces::directx, present::index );
	const auto reset_target = ( void* ) get_virtual( interfaces::directx, reset::index );
	const auto fire_game_event_target = ( void* ) get_virtual( interfaces::engine, fire_game_event::index );
	const auto get_screen_aspect_ratio_target = ( void* ) get_virtual( interfaces::engine, get_screen_aspect_ratio::index );
	const auto is_hltv_target = ( void* ) get_virtual( interfaces::engine, is_hltv::index );
	const auto sv_cheats_bool_target = ( void* ) utilities::find_sig_ida( "engine.dll", "8B 51 1C 3B D1 75 06 8B 41 30 33 C1 C3 8B 02 8B CA FF 60 34 CC CC CC CC CC CC CC CC CC CC CC CC 55 8B EC 83 E4 F8 0F 54 05" );
	const auto draw_model_exec_target = ( void* ) get_virtual( interfaces::model_render, draw_model_exec::index );
	const auto extra_bones_processing_target = ( void* ) utilities::find_sig_ida( "client.dll", "55 8B EC 83 E4 F8 81 EC FC 00 00 00 53 56 8B F1 57" );
	const auto get_eye_ang_target = ( void* ) utilities::find_sig_ida( "client.dll", "56 8B F1 85 F6 74 32" );
	const auto setup_bones_target = ( void* ) utilities::find_sig_ida( "client.dll", "55 8B EC 83 E4 F0 B8 ? ? ? ? E8 ? ? ? ? 56 57 8B F9" );
	const auto update_clientside_animation_target = ( void* ) utilities::find_sig_ida( "client.dll", "55 8B EC 51 56 8B F1 80 BE ? ? ? ? ? 74 36" );
	const auto lock_cursor_target = ( void* ) utilities::find_sig_ida( "vguimatsurface.dll", "80 3D ? ? ? ? 00 8B 91 A4 02 00 00 8B 0D ? ? ? ? C6 05 ? ? ? ? 01" );

	/* init minhook */
	MH_Initialize( );

	/* create minhooks */
	MH_CreateHook( list_leaves_in_box_target, list_leaves_in_box::hook, ( void** ) &o_listleavesinbox );
	MH_CreateHook( frame_stage_target, frame_stage::hook, ( void** ) &o_framestage );
	MH_CreateHook( create_move_target, create_move::hook, ( void** ) &o_createmove );
	MH_CreateHook( get_viewmodel_fov_target, get_viewmodel_fov::hook, ( void** ) &o_viewmdlfov );
	MH_CreateHook( override_view_target, override_view::hook, ( void** ) &o_overrideview );
	MH_CreateHook( end_scene_target, end_scene::hook, ( void** ) &o_endscene );
	MH_CreateHook( present_target, present::hook, ( void** ) &o_present );
	MH_CreateHook( reset_target, reset::hook, ( void** ) &o_reset );
	MH_CreateHook( fire_game_event_target, fire_game_event::hook, ( void** ) &o_fireevent );
	MH_CreateHook( get_screen_aspect_ratio_target, get_screen_aspect_ratio::hook, ( void** ) &o_aspectratio );
	MH_CreateHook( is_hltv_target, is_hltv::hook, ( void** ) &o_ishltv );
	MH_CreateHook( sv_cheats_bool_target, sv_cheats_bool::hook, ( void** ) &o_svcheatsbool );
	MH_CreateHook( draw_model_exec_target, draw_model_exec::hook, ( void** ) &o_drawmodelexec );
	MH_CreateHook( extra_bones_processing_target, do_extra_bones_processing::hook, ( void** ) &o_extrabonesprocessing );
	MH_CreateHook( get_eye_ang_target, get_eye_ang::hook, ( void** ) &o_eyeang );
	MH_CreateHook( setup_bones_target, setup_bones::hook, ( void** ) &o_setupbones );
	MH_CreateHook( update_clientside_animation_target, update_clientside_animation::hook, ( void** ) &o_updateclientanim );
	MH_CreateHook( lock_cursor_target, lock_cursor::hook, ( void** ) &o_lockcursor );

	/* enable all minhook */
	MH_EnableHook( MH_ALL_HOOKS );

	/* init event manager */
	event_mgr.initialize( );

	return true;
}

void hooks::release( ) {
	/* remove minhook */
	MH_Uninitialize( );

	/* remove all hooks */
	MH_RemoveHook( MH_ALL_HOOKS );

	/* disable all minhooks */
	MH_DisableHook( MH_ALL_HOOKS );

	/* restore events */
	event_mgr.restore( );

	/* shutdown imgui */
	ImGui_ImplDX9_Shutdown( );

	/* restore wnd_proc */
	SetWindowLongPtr( csgo_window, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( orig_wnd_proc ) );
}
