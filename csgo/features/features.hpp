#pragma once
#include "../main.hpp"

namespace prediction {
	void start( c_usercmd* cmd );
	void end( );

	inline float old_cur_time;
	inline float old_frame_time;
	inline uintptr_t prediction_random_seed = NULL;
}

