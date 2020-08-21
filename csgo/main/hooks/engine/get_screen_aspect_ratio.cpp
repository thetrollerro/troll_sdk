#include "../hooks.hpp"

float __fastcall hooks::get_screen_aspect_ratio::hook( void* ecx, void* edx, int x, int y ) {

	return ( ( float ) x / y );

	o_aspectratio( interfaces::engine, edx, x, y );
}