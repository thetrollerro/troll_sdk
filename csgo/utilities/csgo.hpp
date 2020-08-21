#pragma once
#include <windows.h>
#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <array>
#include <fstream>
#include <istream>
#include <unordered_map>
#include <intrin.h>
#include "utilities.hpp"
#include "../minhook/minhook.h"
#include "../interfaces/interfaces.hpp"
#include "../sdk/sdk.hpp"
#include "../main/hooks/hooks.hpp"
#include "../math/math.hpp"
#include "../utilities/renderer/renderer.hpp"
#include "../sdk/math/matrix.hpp"
#include "../main/menu/imgui/imgui.h"
#include "../main/menu/imgui/impl/imgui_impl_dx9.h"

namespace g {
	extern c_usercmd* cmd;
	extern bool send_packet;
	extern vec3_t real_angle;
	extern vec3_t fake_angle;
}