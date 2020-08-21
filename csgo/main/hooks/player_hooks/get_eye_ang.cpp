#include "../hooks.hpp"

vec3_t* __fastcall hooks::get_eye_ang::hook( void* ecx, void* edx ) {
	if ( !g_local || !interfaces::engine->is_in_game( ) ) return o_eyeang( ecx, edx );
	if ( ecx != g_local ) return o_eyeang( ecx, edx );

	static auto ret_to_thirdperson_pitch = utilities::find_sig_ida( "client.dll", "8B CE F3 0F 10 00 8B 06 F3 0F 11 45 ? FF 90 ? ? ? ? F3 0F 10 55 ?" );
	static auto ret_to_thirdperson_yaw = utilities::find_sig_ida( "client.dll", "F3 0F 10 55 ? 51 8B 8E ? ? ? ?" );

	if ( _ReturnAddress( ) == ( void* ) ret_to_thirdperson_pitch || _ReturnAddress( ) == ( void* ) ret_to_thirdperson_yaw )
		return g::cmd ? &g::cmd->viewangles : &g_local->m_angEyeAngles( );

	return o_eyeang( ecx, edx );
}