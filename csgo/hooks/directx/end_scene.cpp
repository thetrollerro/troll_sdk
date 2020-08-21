#include "../hooks.hpp"

void hooks::dx_things( IDirect3DDevice9* dev ) {
	if ( !menu::d3d_init ) {
		/* init menu tryle */
		menu::style( dev );

		/* we already initialized, stop now */
		menu::d3d_init = true;
	}

	/* backup render states */
	IDirect3DStateBlock9* stateBlock = nullptr;
	IDirect3DVertexDeclaration9* vertDec = nullptr;
	dev->GetVertexDeclaration( &vertDec );
	dev->CreateStateBlock( D3DSBT_PIXELSTATE, &stateBlock );

	/* menu here */
	menu::init( );

	/* restore now */
	stateBlock->Apply( );
	stateBlock->Release( );
	dev->SetVertexDeclaration( vertDec );
}

long __stdcall hooks::end_scene::hook( IDirect3DDevice9* dev ) {
	/* end_scene gets called twice by csgo so we call it once */
	static auto ret = _ReturnAddress( );
	if ( ret != _ReturnAddress( ) ) {
		return o_endscene( dev );
	}

	/* call dx features */
	dx_things( dev );

	return o_endscene( dev );
}