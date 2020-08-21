#pragma once
#include <vector>
#include <string>
#include <iostream>

inline int selectedcfg = 0;
inline std::vector<std::string> configs;
inline std::string cfgname = "default";

extern void get_config( );

template <typename t>
class config_item
{
	std::string category, name;
	t* value;
public:
	config_item( std::string category, std::string name, t* value )
	{
		this->category = category;
		this->name = name;
		this->value = value;
	}
};

template <typename t>
class config_value
{
public:
	config_value( std::string category_, std::string name_, t* value_ )
	{
		category = category_;
		name = name_;
		value = value_;
	}

	std::string category, name;
	t* value;
};

class vars {
public:
	struct misc {
		char config_name[ 52 ];
		bool unload = false;
	}misc;


protected:
	std::vector<config_value<int>*> ints;
	std::vector<config_value<bool>*> bools;
	std::vector<config_value<float>*> floats;
private:
	void setup_value( int&, int, std::string, std::string );
	void setup_value( bool&, bool, std::string, std::string );
	void setup_value( float&, float, std::string, std::string );
public:
	vars( )
	{
		setup_config( );
	}

	void setup_config( );

	void save_config( );
	void load_config( );
private:
	void save_ragebot( );
	void save_antiaim( );
	void save_legitbot( );
	void save_esp( );
	void save_misc( );
	void save_skins( );
};
inline vars g_vars;
