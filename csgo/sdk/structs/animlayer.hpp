#pragma once
#include <cstdint>

struct animlayer_t {
	uint8_t pad0x0[ 20 ];
	int	order;
	int	sequence;
	float previous_cycle;
	float weight;
	float weight_delta_rate;
	float playback_rate;
	float cycle;
	void* owner;
	uint8_t pad0x1[ 4 ];
};
