#include "vars.hpp"
#include <winerror.h>
#include <ShlObj.h>
#include <string>
#include <sstream>

void vars::setup_config( ) {
	save_ragebot( );
	save_antiaim( );
	save_legitbot( );
	save_esp( );
	save_misc( );
	save_skins( );
}

void vars::save_ragebot( ) {
}

void vars::save_antiaim( ) {
}

void vars::save_legitbot( ) {
}

void vars::save_esp( ) {
}

void vars::save_misc( ) {
}

void vars::save_skins( ) {
}

void vars::setup_value( int& value, int def, std::string category, std::string name )
{
	value = def;
	ints.push_back( new config_value<int>( category, name, &value ) );
}

void vars::setup_value( float& value, float def, std::string category, std::string name )
{
	value = def;
	floats.push_back( new config_value<float>( category, name, &value ) );
}

void vars::setup_value( bool& value, bool def, std::string category, std::string name )
{
	value = def;
	bools.push_back( new config_value<bool>( category, name, &value ) );
}

void get_config( )
{
	//get all files on folder

	configs.clear( );

	static char path[ MAX_PATH ];
	std::string szPath1;

	if ( !SUCCEEDED( SHGetFolderPathA( NULL, CSIDL_MYDOCUMENTS, NULL, 0, path ) ) )
		return;

	szPath1 = std::string( path ) + "\\TrollerWare.xyz\\*";


	WIN32_FIND_DATA FindFileData;
	HANDLE hf;

	configs.push_back( "choose config" );

	hf = FindFirstFile( szPath1.c_str( ), &FindFileData );
	if ( hf != INVALID_HANDLE_VALUE ) {
		do {
			std::string filename = FindFileData.cFileName;

			if ( filename == "." )
				continue;

			if ( filename == ".." )
				continue;

			if ( !( FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
			{
				if ( filename.find( ".cfg" ) != std::string::npos )
				{
					configs.push_back( std::string( filename ) );
				}
			}
		} while ( FindNextFile( hf, &FindFileData ) != 0 );
		FindClose( hf );
	}
}

void vars::save_config( )
{
	static char path[ MAX_PATH ];
	std::string folder, file;

	if ( SUCCEEDED( SHGetFolderPathA( NULL, CSIDL_MYDOCUMENTS, NULL, 0, path ) ) )
	{
		char szCmd[ 256 ];
		sprintf( szCmd, "\\TrollerWare.xyz\\%s.cfg", g_vars.misc.config_name );

		folder = std::string( path ) + "\\TrollerWare.xyz\\";
		file = std::string( path ) + szCmd;
	}

	CreateDirectoryA( folder.c_str( ), NULL );

	for ( auto value : ints )
		WritePrivateProfileStringA( value->category.c_str( ), value->name.c_str( ), std::to_string( *value->value ).c_str( ), file.c_str( ) );

	for ( auto value : floats )
		WritePrivateProfileStringA( value->category.c_str( ), value->name.c_str( ), std::to_string( *value->value ).c_str( ), file.c_str( ) );

	for ( auto value : bools )
		WritePrivateProfileStringA( value->category.c_str( ), value->name.c_str( ), *value->value ? "true" : "false", file.c_str( ) );
}

void vars::load_config( )
{
	static char path[ MAX_PATH ];
	std::string folder, file;

	if ( SUCCEEDED( SHGetFolderPathA( NULL, CSIDL_MYDOCUMENTS, NULL, 0, path ) ) )
	{
		char szCmd[ 256 ];
		sprintf( szCmd, "\\TrollerWare.xyz\\%s.cfg", g_vars.misc.config_name );

		folder = std::string( path ) + "\\TrollerWare.xyz\\";
		file = std::string( path ) + szCmd;
	}

	CreateDirectoryA( folder.c_str( ), NULL );

	char value_l[ 32 ] = { '\0' };

	for ( auto value : ints )
	{
		GetPrivateProfileStringA( value->category.c_str( ), value->name.c_str( ), "", value_l, 32, file.c_str( ) );
		*value->value = atoi( value_l );
	}

	for ( auto value : floats )
	{
		GetPrivateProfileStringA( value->category.c_str( ), value->name.c_str( ), "", value_l, 32, file.c_str( ) );
		*value->value = atof( value_l );
	}

	for ( auto value : bools )
	{
		GetPrivateProfileStringA( value->category.c_str( ), value->name.c_str( ), "", value_l, 32, file.c_str( ) );
		*value->value = !strcmp( value_l, "true" );
	}
}