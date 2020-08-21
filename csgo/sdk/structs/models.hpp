#pragma once
#include "../math/vector3d.hpp"
#include "../classes/studio.hpp"

struct model_t {
	void* handle;
	char name[ 260 ];
	int loadFlags;
	int serverCount;
	int type;
	int flags;
	vec3_t  vecMins;
	vec3_t  vecMaxs;
	float   radius;
};

struct model_render_info_t {
	vec3_t origin;
	vec3_t angles;
	char pad[ 0x4 ]; // added this
	void* renderable; // this
	//const void *model; // and this
	const model_t* model;
	const matrix_t* model_to_world;
	const matrix_t* lighting_offset;
	const vec3_t* lighting_origin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	unsigned short instance;

	model_render_info_t( ) {
		model_to_world = NULL;
		lighting_offset = NULL;
		lighting_origin = NULL;
	}
};
struct studiohwdata_t;
typedef void* studio_decal_handle_t;
class i_client_renderable;
struct draw_model_state_t {
	studio_hdr_t* studio_hdr;
	studiohwdata_t* studio_hwdara;
	i_client_renderable* renderable;
	const matrix_t* model_to_world;
	studio_decal_handle_t     m_decals;
	int                     m_drawflags;
	int                     m_lod;
};
