#pragma once
#include <windows.h>
#include <cstdint>
#include <string>
#include <stdexcept>

#include "classes/i_base_client_dll.hpp"
#include "classes/i_client_entity_list.hpp"
#include "classes/iv_engine_client.hpp"
#include "classes/i_client_state.hpp"
#include "classes/i_panel.hpp"
#include "classes/i_surface.hpp"
#include "classes/c_global_vars_base.hpp"
#include "classes/i_material_system.hpp"
#include "classes/iv_model_info.hpp"
#include "classes/iv_model_render.hpp"
#include "classes/iv_debug_overlay.hpp"
#include "classes/i_game_event_manager.hpp"
#include "classes/i_input.hpp"
#include "classes/i_client_mode.hpp"
#include "classes/i_input_system.hpp"
#include "classes/i_trace.hpp"
#include "classes/glow_manager.hpp"
#include "classes/i_player_movement.hpp"
#include "classes/i_cvar.hpp"
#include "classes/physic_props.hpp"
#include "classes/c_mem_alloc.hpp"
#include "classes/i_prediction.hpp"
#include <d3d9.h>

namespace interfaces {
	/* credits: gladiatorcheatz */
	class interface_reg
	{
	private:
		using InstantiateInterfaceFn = void* ( * )( );
	public:
		InstantiateInterfaceFn create_fn;
		const char* name;
		interface_reg* next;
	};

	template<typename T>
	static T* get_interface( const char* modName, const char* ifaceName, bool exact = false )
	{
		T* i_interface = nullptr;
		interface_reg* interface_reg_list;
		int partMatchLen = strlen( ifaceName );

		DWORD interface_fn = reinterpret_cast< DWORD >( GetProcAddress( GetModuleHandleA( modName ), "CreateInterface" ) );

		if ( !interface_fn )
			return nullptr;

		unsigned int jmp_start = ( unsigned int ) ( interface_fn ) +4;
		unsigned int jmp_target = jmp_start + *( unsigned int* ) ( jmp_start + 1 ) + 5;

		interface_reg_list = **reinterpret_cast< interface_reg*** >( jmp_target + 6 );

		for ( interface_reg* cur = interface_reg_list; cur; cur = cur->next )
		{
			if ( exact == true )
			{
				if ( strcmp( cur->name, ifaceName ) == 0 )
					i_interface = reinterpret_cast< T* >( cur->create_fn( ) );
			}
			else
			{
				if ( !strncmp( cur->name, ifaceName, partMatchLen ) && std::atoi( cur->name + partMatchLen ) > 0 )
					i_interface = reinterpret_cast< T* >( cur->create_fn( ) );
			}
		}
		return i_interface;
	}

	inline i_base_client_dll* client;
	inline i_input* input;
	inline i_client_entity_list* entity_list;
	inline iv_engine_client* engine;
	inline i_client_mode* clientmode;
	inline i_client_state* clientstate;
	inline i_panel* panel;
	inline i_surface* surface;
	inline c_global_vars_base* globals;
	inline i_material_system* material_system;
	inline iv_model_info* model_info;
	inline iv_model_render* model_render;
	inline iv_debug_overlay* debug_overlay;
	inline i_game_event_manager* event_manager;
	inline i_inputsytem* inputsystem;
	inline IDirect3DDevice9* directx;
	inline DWORD* input_internal;
	inline i_trace* trace_ray;
	inline glow_manager_t* glow_manager;
	inline i_player_movement* game_movement;
	inline i_prediction* prediction;
	inline c_move_helper* move_helper;
	inline i_cvar* cvar;
	inline physic_props* props;
	inline c_mem_alloc* memalloc;

	bool initialize( );
}