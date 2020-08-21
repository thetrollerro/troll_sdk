#pragma once
#include <cstdint>
#include "i_trace.hpp"

#pragma pack(push, 1)

class c_clock_drift_mgr
{
public:
	float clock_offsets[ 16 ];   //0x0000
	uint32_t cur_clock_offsets; //0x0044
	uint32_t server_tick;     //0x0048
	uint32_t client_tick;     //0x004C
}; //Size: 0x0050

class c_event_info
{
public:

	uint16_t class_id; //0x0000 0 implies not in use
	char pad_0002[ 2 ]; //0x0002 
	float fire_delay; //0x0004 If non-zero, the delay time when the event should be fired ( fixed up on the client )
	char pad_0008[ 4 ]; //0x0008
	c_client_class* client_class; //0x000C
	void* data; //0x0010 Raw event data
	char pad_0014[ 48 ]; //0x0014
}; //Size: 0x0044

class i_net_channel;
class i_client_state {
public:
	void force_full_update( ) {
		*reinterpret_cast< int* >( std::uintptr_t( this ) + 0x174 ) = -1;
	}

	char pad_0000[ 156 ];             //0x0000
	i_net_channel* net_channel;      //0x009C
	uint32_t challenge_nr;        //0x00A0
	char pad_00A4[ 100 ];             //0x00A4
	uint32_t signon_state;        //0x0108
	char pad_010C[ 8 ];               //0x010C
	float next_cmd_time;          //0x0114
	uint32_t server_count;        //0x0118
	uint32_t current_sequence;    //0x011C
	char pad_0120[ 8 ];               //0x0120
	c_clock_drift_mgr clock_drift_mgr; //0x0128
	uint32_t delta_tick;          //0x0174
	bool paused;                 //0x0178
	char pad_017D[ 3 ];               //0x017D
	uint32_t view_entity;         //0x0180
	uint32_t player_slow;         //0x0184
	char level_name[ 260 ];        //0x0188
	char level_name_short[ 80 ];    //0x028C
	char group_name[ 80 ];         //0x02DC
	char pad_032Ñ[ 92 ];              //0x032Ñ
	uint32_t max_clients;         //0x0388
	char pad_0314[ 18824 ];           //0x0314
	float last_server_tick_time;   //0x4C98
	bool in_simulation;              //0x4C9C
	char pad_4C9D[ 3 ];               //0x4C9D
	uint32_t old_tickcount;          //0x4CA0
	float tick_remainder;          //0x4CA4
	float frame_time;              //0x4CA8
	int lastout_going_command;        //0x4CAC
	int choked_commands;             //0x4CB0
	int last_command_ack;           //0x4CB4
	int command_ack;                //0x4CB8
	int sound_sequence;           //0x4CBC
	char pad_4CC0[ 80 ];              //0x4CC0
	vec3_t viewangles;              //0x4D10
	char pad_4D1C[ 208 ];             //0x4D1C
	c_event_info* events; //0x4DEC
	std::uint32_t& choked( ) {
		return *reinterpret_cast< std::uint32_t* >( reinterpret_cast< std::uintptr_t >( this ) + 0x4D28 );
	}
};

#pragma pack(pop)