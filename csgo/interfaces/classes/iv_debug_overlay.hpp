#pragma once
#include "../../sdk/math/vector3d.hpp"
#include "../../utilities/utilities.hpp"
#include "../../sdk/math/matrix.hpp"
class overlay_text_t;

class iv_debug_overlay {
public:
    virtual void            __unkn( ) = 0;
    virtual void            add_entity_text_overlay( int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char* format, ... ) = 0;
    virtual void            add_box_overlay( const vec3_t& origin, const vec3_t& mins, const vec3_t& max, vec3_t const& orientation, int r, int g, int b, int a, float duration ) = 0;
    virtual void            add_sphere_overlay( const vec3_t& vorigin, float flradius, int ntheta, int nphi, int r, int g, int b, int a, float flDuration ) = 0;
    virtual void            add_triangle_overlay( const vec3_t& p1, const vec3_t& p2, const vec3_t& p3, int r, int g, int b, int a, bool nodepthTest, float duration ) = 0;
    virtual void            add_line_overlay( const vec3_t& origin, const vec3_t& dest, int r, int g, int b, bool nodepthtest, float duration ) = 0;
    virtual void            add_text_overlay( const vec3_t& origin, float duration, const char* format, ... ) = 0;
    virtual void            add_text_overlay( const vec3_t& origin, int line_offset, float duration, const char* format, ... ) = 0;
    virtual void            add_screen_text_overlay( float flxpos, float flypos, float flduration, int r, int g, int b, int a, const char* text ) = 0;
    virtual void            add_swept_box_overlay( const vec3_t& start, const vec3_t& end, const vec3_t& mins, const vec3_t& max, const vec3_t& angles, int r, int g, int b, int a, float flDuration ) = 0;
    virtual void            add_grid_overlay( const vec3_t& origin ) = 0;
    virtual void            add_coord_frame_overlay( const matrix_t& frame, float flscale, int vcolortable[ 3 ][ 3 ] = nullptr ) = 0;
    virtual int             screen_position( const vec3_t& point, vec3_t& screen ) = 0;
    virtual int             screen_position( float flxpos, float flypos, vec3_t& screen ) = 0;
    virtual overlay_text_t* get_first( void ) = 0;
    virtual overlay_text_t* get_next( overlay_text_t* current ) = 0;
    virtual void            clear_dead_overlays( void ) = 0;
    virtual void            clear_all_overlays( ) = 0;
    virtual void            add_text_overlayrgb( const vec3_t& origin, int line_offset, float duration, float r, float g, float b, float alpha, const char* format, ... ) = 0;
    virtual void            add_text_overlayrgb( const vec3_t& origin, int line_offset, float duration, int r, int g, int b, int a, const char* format, ... ) = 0;
    virtual void            add_line_overlay_alpha( const vec3_t& origin, const vec3_t& dest, int r, int g, int b, int a, bool nodepthtest, float duration ) = 0;
    virtual void            add_box_overlay2( const vec3_t& origin, const vec3_t& mins, const vec3_t& max, vec3_t const& orientation, const uint8_t* faceColor, const uint8_t* edgeColor, float duration ) = 0;
    virtual void            purge_text_overlays( ) = 0;
    virtual void            draw_pill( const vec3_t& mins, const vec3_t& max, float& diameter, int r, int g, int b, int a, float duration ) = 0;
    void add_capsule_overlay( vec3_t& mins, vec3_t& maxs, float pillradius, int r, int g, int b, int a, float duration ) {
        using o_fn = void( __thiscall* )( void*, vec3_t&, vec3_t&, float&, int, int, int, int, float );
        utilities::call_virtual<o_fn>( this, 24 )( this, mins, maxs, pillradius, r, g, b, a, duration );
    }
};