#include "interfaces.hpp"
#include "../main.hpp"

bool interfaces::initialize( ) {
	client = get_interface<i_base_client_dll>( "client.dll", "VClient018", true );
	entity_list = get_interface<i_client_entity_list>( "client.dll", "VClientEntityList003", true );
	engine = get_interface<iv_engine_client>( "engine.dll", "VEngineClient014", true );
	panel = get_interface<i_panel>( "vgui2.dll", "VGUI_Panel009", true );
	surface = get_interface<i_surface>( "vguimatsurface.dll", "VGUI_Surface031", true );
	material_system = get_interface<i_material_system>( "materialsystem.dll", "VMaterialSystem080", true );
	model_info = get_interface<iv_model_info>( "engine.dll", "VModelInfoClient004", true );
	model_render = get_interface<iv_model_render>( "engine.dll", "VEngineModel016", true );
	cvar = get_interface<i_cvar>( "vstdlib.dll", "VEngineCvar007", true );
	event_manager = get_interface<i_game_event_manager>( "engine.dll", "GAMEEVENTSMANAGER002", true );
	debug_overlay = get_interface<iv_debug_overlay>( "engine.dll", "VDebugOverlay004", true );
	inputsystem = get_interface<i_inputsytem>( "inputsystem.dll", "InputSystemVersion001", true );
	trace_ray = get_interface<i_trace>( "engine.dll", "EngineTraceClient004", true );
	game_movement = get_interface<i_player_movement>( "client.dll", "GameMovement001", true );
	prediction = get_interface<i_prediction>( "client.dll", "VClientPrediction001", true );
	props = get_interface<physic_props>( "vphysics.dll", "VPhysicsSurfaceProps001", true );
	input_internal = get_interface<DWORD>( "vgui2.dll", "VGUI_InputInternal001", true );
	memalloc = *reinterpret_cast< c_mem_alloc** >( GetProcAddress( GetModuleHandleA( "tier0.dll" ), "g_pMemAlloc" ) );

	/*custom interfaces*/
	clientmode = **( i_client_mode*** ) ( ( *( DWORD** ) client )[ 10 ] + 0x5 );
	globals = **( c_global_vars_base*** ) ( ( *( DWORD** ) client )[ 11 ] + 10 );

	clientstate = **( i_client_state*** ) ( utilities::find_sig_ida( "engine.dll", "A1 ? ? ? ? 8B 80 ? ? ? ? C3" ) + 1 );
	directx = **( IDirect3DDevice9*** ) ( utilities::find_sig_ida( "shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) + 1 );
	input = *( i_input** ) ( utilities::find_sig_ida( "client.dll", "B9 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? B8 ? ? ? ?" ) + 7 );
	glow_manager = ( glow_manager_t* ) ( *( uintptr_t* ) ( utilities::find_sig_ida( "client.dll", "0F 11 05 ? ? ? ? 83 C8 01 C7 05 ? ? ? ? 00 00 00 00" ) + 3 ) );
	move_helper = **( c_move_helper*** ) ( utilities::find_sig_ida( "client.dll", "8B 0D ? ? ? ? 8B 46 08 68" ) + 2 );

	return true;
}