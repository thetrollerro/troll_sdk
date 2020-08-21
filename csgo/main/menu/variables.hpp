#pragma once

class variables {
public:
	struct misc {
		char config_name[ 52 ];
		bool unload = false;
	}misc;
};
inline variables g_vars;
