#pragma once
#include <cstdint>
#include <cmath>

class weapon_info_t {
public:
	uint8_t pad0[ 0x14 ];
	uint32_t max_clip;
	uint8_t pad1[ 0xC ];
	uint32_t max_reserved_ammo;
	uint8_t pad2[ 0x60 ];
	char* hud_name;
	char* weapon_name;
	uint8_t pad3[ 0x38 ];
	uint32_t weapon_type;
	uint8_t pad4[ 0x4 ];
	uint32_t price;
	uint32_t reward;
	uint8_t pad5[ 0x4 ];
	float_t fire_rate;
	uint8_t pad6[ 0xC ];
	uint8_t full_auto;
	uint8_t pad7[ 0x3 ];
	uint32_t dmg;
	float_t armor_ratio;
	uint32_t bullets;
	float_t penetration;
	uint8_t pad8[ 0x8 ];
	float_t range;
	float_t range_modifier;
	uint8_t pad9[ 0x10 ];
	uint8_t has_silencer;
	uint8_t pad10[ 0xF ];
	float_t max_speed;
	float_t max_speed_alt;
	uint8_t pad11[ 0x4C ];
	uint32_t recoil_seed;
	uint8_t pad12[ 0x20 ];
};