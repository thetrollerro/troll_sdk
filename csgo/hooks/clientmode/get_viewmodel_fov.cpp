#include "../hooks.hpp"

float __fastcall hooks::get_viewmodel_fov::hook( void* ecx, void* edx ) {
	return o_viewmdlfov( interfaces::clientmode, edx );
}
