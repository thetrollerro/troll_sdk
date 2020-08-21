#pragma once
#include "../math/vector3d.hpp"
#include "../../utilities/checksum_crc/checksum_crc.hpp"

enum cmd_buttons {
	in_attack = ( 1 << 0 ),
	in_jump = ( 1 << 1 ),
	in_duck = ( 1 << 2 ),
	in_forward = ( 1 << 3 ),
	in_back = ( 1 << 4 ),
	in_use = ( 1 << 5 ),
	in_cancel = ( 1 << 6 ),
	in_left = ( 1 << 7 ),
	in_right = ( 1 << 8 ),
	in_moveleft = ( 1 << 9 ),
	in_moveright = ( 1 << 10 ),
	in_attack2 = ( 1 << 11 ),
	in_run = ( 1 << 12 ),
	in_reload = ( 1 << 13 ),
	in_alt1 = ( 1 << 14 ),
	in_alt2 = ( 1 << 15 ),
	in_smain = ( 1 << 16 ),
	in_speed = ( 1 << 17 ),
	in_walk = ( 1 << 18 ),
	in_zoom = ( 1 << 19 ),
	in_weapon1 = ( 1 << 20 ),
	in_weapon2 = ( 1 << 21 ),
	in_bullrush = ( 1 << 22 ),
	in_grenade1 = ( 1 << 23 ),
	in_grenade2 = ( 1 << 24 ),
	in_attack3 = ( 1 << 25 )
};

class c_usercmd {
public:
	c_usercmd( )
	{
		memset( this, 0, sizeof( *this ) );
	};
	virtual ~c_usercmd( ) {};

	CRC32_t get_checksum( void ) const {
		CRC32_t crc;
		CRC32_Init( &crc );

		CRC32_ProcessBuffer( &crc, &command_number, sizeof( command_number ) );
		CRC32_ProcessBuffer( &crc, &tick_count, sizeof( tick_count ) );
		CRC32_ProcessBuffer( &crc, &viewangles, sizeof( viewangles ) );
		CRC32_ProcessBuffer( &crc, &aimdirection, sizeof( aimdirection ) );
		CRC32_ProcessBuffer( &crc, &forwardmove, sizeof( forwardmove ) );
		CRC32_ProcessBuffer( &crc, &sidemove, sizeof( sidemove ) );
		CRC32_ProcessBuffer( &crc, &upmove, sizeof( upmove ) );
		CRC32_ProcessBuffer( &crc, &buttons, sizeof( buttons ) );
		CRC32_ProcessBuffer( &crc, &impulse, sizeof( impulse ) );
		CRC32_ProcessBuffer( &crc, &weaponselect, sizeof( weaponselect ) );
		CRC32_ProcessBuffer( &crc, &weaponsubtype, sizeof( weaponsubtype ) );
		CRC32_ProcessBuffer( &crc, &random_seed, sizeof( random_seed ) );
		CRC32_ProcessBuffer( &crc, &mousedx, sizeof( mousedx ) );
		CRC32_ProcessBuffer( &crc, &mousedy, sizeof( mousedy ) );

		CRC32_Final( &crc );
		return crc;
	}

	int command_number; // 0x04 
	int tick_count; // 0x08 
	vec3_t viewangles; // 0x0C 
	vec3_t aimdirection; // 0x18
	float forwardmove; // 0x24
	float sidemove; // 0x28
	float upmove; // 0x2C
	int buttons; // 0x30 
	char impulse; // 0x34
	int weaponselect; // 0x38 
	int weaponsubtype; // 0x3C
	int random_seed; // 0x40 
	short mousedx; // 0x44 
	short mousedy; // 0x46 
	bool hasbeenpredicted; // 0x48 
	uint8_t pad_1[ 0x18 ]; // 0x4C 
};

class c_verified_usercmd
{
public:
	c_usercmd m_cmd;
	CRC32_t  m_crc;
};
