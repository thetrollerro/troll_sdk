#include "main.hpp"
#include "features/features.hpp"
HINSTANCE this_mod;

void dll_on_attach( ) {

	/* wait for all modules to load */
	while ( !GetModuleHandleA( "serverbrowser.dll" ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

	MessageBox( 0, "changed animfix credits to Halogen and some fps fixes", "TrollerWare.xyz", MB_OK | MB_ICONINFORMATION );

	/* initialize csgo hack */
	interfaces::initialize( );
	netvars::init( );
	hooks::initialize( );

	/* wait for unload key */
	while ( !g_vars.misc.unload )
		std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

	/* unload */
	hooks::release( );

	fclose( ( FILE* ) stdin );
	fclose( ( FILE* ) stdout );
	FreeConsole( );

	FreeLibraryAndExitThread( this_mod, 0 );
}

BOOL WINAPI DllMain( HINSTANCE instance, DWORD reason, LPVOID reserved ) {
	/* attach csgo hake */
	if ( reason == DLL_PROCESS_ATTACH )
		CreateThread( nullptr, 0, ( LPTHREAD_START_ROUTINE ) dll_on_attach, HMODULE( instance ), 0, nullptr );

	return true;
}
