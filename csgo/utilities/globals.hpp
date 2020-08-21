#pragma once
#include "../sdk/classes/c_usercmd.hpp"
#include "../sdk/math/vector3d.hpp"

namespace g {
	extern c_usercmd* cmd;
	extern bool send_packet;
	extern vec3_t real_angle;
	extern vec3_t fake_angle;
}