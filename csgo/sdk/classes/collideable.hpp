#pragma once
#include "../math/vector3d.hpp"
#include "../structs/models.hpp"
#include "../../interfaces/classes/i_trace.hpp"
class i_client_unknown;
class collideable_t {
public:
	virtual i_handle_entity* get_entity_handle( ) = 0;
	virtual vec3_t& mins( ) const = 0;
	virtual vec3_t& maxs( ) const = 0;
	virtual void world_space_trigger_bounds( vec3_t* world_mins, vec3_t* world_maxs ) const = 0;
	virtual bool test_collision( ray_t ray, uint32_t contents_mask, trace_t& trace ) = 0;
	virtual bool test_hitboxes( ray_t ray, uint32_t contents_mask, trace_t& trace ) = 0;
	virtual int get_collision_model_index( ) = 0;
	virtual const model_t* get_collision_model( ) = 0;
	virtual const vec3_t& get_collision_origin( ) const = 0;
	virtual const vec3_t& get_collision_angles( ) const = 0;
	virtual const matrix_t& collision_to_world_transform( ) const = 0;
	virtual uint32_t get_solid( ) const = 0;
	virtual uint32_t solid_flags( ) const = 0;
	virtual i_client_unknown* get_client_unknown( ) = 0;
	virtual int get_collision_group( ) const = 0;
	virtual void world_space_surrounding_bounds( vec3_t* pVecMins, vec3_t* pVecMaxs ) = 0;
	virtual bool should_touch_trigger( int triggerSolidFlags ) const = 0;
	virtual const matrix_t* get_root_parent_to_world_transform( ) const = 0;
};