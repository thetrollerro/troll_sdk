#pragma once
#include "../../sdk/structs/materials.hpp"
#define declare_pointer_handle(name) struct name##__ { int unused; }; typedef struct name##__ *name
#define maxstudioskins		32

// these are given to findmaterial to reference the texture groups that Show up on the
#define texture_group_lightmap						        "Lightmaps"
#define texture_group_world							          "World textures"
#define texture_group_model							          "Model textures"
#define texture_group_vgui							          "VGUI textures"
#define texture_group_particle						        "Particle textures"
#define texture_group_decal							          "Decal textures"
#define texture_group_skybox						          "SkyBox textures"
#define texture_group_client_effects				      "ClientEffect textures"
#define texture_group_other							          "Other textures"
#define texture_group_precached						        "Precached"
#define texture_group_cube_map						        "CubeMap textures"
#define texture_group_render_target					      "RenderTargets"
#define texture_group_unaccounted					        "Unaccounted textures"
//#define texture_group_static_vertex_buffer		  "Static Vertex"
#define texture_group_static_index_buffer			    "Static Indices"
#define texture_group_static_vertex_buffer_disp		"Displacement Verts"
#define texture_group_static_vertex_buffer_color	"Lighting Verts"
#define texture_group_static_vertex_buffer_world	"World Verts"
#define texture_group_static_vertex_buffer_models	"Model Verts"
#define texture_group_static_vertex_buffer_other	"Other Verts"
#define texture_group_dynamic_index_buffer			  "Dynamic Indices"
#define texture_group_dynamic_vertex_buffer			  "Dynamic Verts"
#define texture_group_depth_buffer					      "DepthBuffer"
#define texture_group_view_model					        "ViewModel"
#define texture_group_pixel_shaders					      "Pixel Shaders"
#define texture_group_vertex_shaders				      "Vertex Shaders"
#define texture_group_render_target_surface			  "RenderTarget Surfaces"
#define texture_group_morph_targets					      "Morph Targets"

//-----------------------------------------------------------------------------
// forward declarations
//-----------------------------------------------------------------------------

enum compiled_vt_flags
{
	textureflags_pointsample = 0x00000001,
	textureflags_trilinear = 0x00000002,
	textureflags_clamps = 0x00000004,
	textureflags_clampt = 0x00000008,
	textureflags_anisotropic = 0x00000010,
	textureflags_hint_dxt5 = 0x00000020,
	textureflags_pwl_corrected = 0x00000040,
	textureflags_normal = 0x00000080,
	textureflags_nomip = 0x00000100,
	textureflags_nolod = 0x00000200,
	textureflags_all_mips = 0x00000400,
	textureflags_procedural = 0x00000800,
	textureflags_onebitalpha = 0x00001000,
	textureflags_eightbitalpha = 0x00002000,
	textureflags_envmap = 0x00004000,
	textureflags_rendertarget = 0x00008000,
	textureflags_depthrendertarget = 0x00010000,
	textureflags_nodebugoverride = 0x00020000,
	textureflags_singlecopy = 0x00040000,
	textureflags_pre_srgb = 0x00080000,
	textureflags_unused_00100000 = 0x00100000,
	textureflags_unused_00200000 = 0x00200000,
	textureflags_unused_00400000 = 0x00400000,
	textureflags_nodepthbuffer = 0x00800000,
	textureflags_unused_01000000 = 0x01000000,
	textureflags_clampu = 0x02000000,
	textureflags_vertextexture = 0x04000000,
	textureflags_ssbump = 0x08000000,
	textureflags_unused_10000000 = 0x10000000,
	textureflags_border = 0x20000000,
	textureflags_unused_40000000 = 0x40000000,
	textureflags_unused_80000000 = 0x80000000
};

enum standardlightmap_t
{
	material_system_lightmap_page_white = -1,
	material_system_lightmap_page_white_bump = -2,
	material_system_lightmap_page_user_defined = -3
};

struct materialsystem_sortinfo_t
{
	i_material* material;
	int			lightmappageid;
};

enum materialthreadmode_t
{
	material_single_threaded,
	material_queued_single_threaded,
	material_queued_threaded
};

enum materialcontexttype_t
{
	material_hardware_context,
	material_queued_context,
	material_null_context
};

enum
{
	material_adapter_name_length = 512
};

struct materialtextureinfo_t
{
	int iexcludeinformation;
};

struct applicationperformancecountersinfo_t
{
	float msmain;
	float msmst;
	float msgpu;
	float msflip;
	float mstotal;
};

struct applicationinstantcountersinfo_t
{
	uint32_t m_ncpuactivitymask;
	uint32_t m_ndeferredwordsallocated;
};
struct materialadapterinfo_t
{
	char m_pdrivername[ material_adapter_name_length ];
	unsigned int m_vendorid;
	unsigned int m_deviceid;
	unsigned int m_subsysid;
	unsigned int m_revision;
	int m_ndxsupportlevel;			// this is the *preferred* dx support level
	int m_nmindxsupportlevel;
	int m_nmaxdxsupportlevel;
	unsigned int m_ndriverversionhigh;
	unsigned int m_ndriverversionlow;
};

struct materialvideomode_t
{
	int m_width;			// if width and height are 0 and you select
	int m_height;			// windowed mode, it'll use the window size
	image_format m_format;	// use imageformats (ignored for windowed mode)
	int m_refreshrate;		// 0 == default (ignored for windowed mode)
};
enum hdrtype_t
{
	hdr_type_none,
	hdr_type_integer,
	hdr_type_float,
};

enum restorechangeflags_t
{
	material_restore_vertex_format_changed = 0x1,
	material_restore_release_managed_resources = 0x2,
};

enum rendertargetsizemode_t
{
	rt_size_no_change = 0,
	rt_size_default = 1,
	rt_size_picmip = 2,
	rt_size_hdr = 3,
	rt_size_full_frame_buffer = 4,
	rt_size_offscreen = 5,
	rt_size_full_frame_buffer_rounded_up = 6
};

enum materialrendertargetdepth_t
{
	material_rt_depth_shared = 0x0,
	material_rt_depth_separate = 0x1,
	material_rt_depth_none = 0x2,
	material_rt_depth_only = 0x3,
};

typedef unsigned short materialhandle_t;

class i_material_system {
public:
	i_material* find_material( const char* name, const char* group = nullptr ) {
		using o_fn = i_material * ( __thiscall* )( void*, const char*, const char* );
		return utilities::call_virtual< o_fn >( this, 84 )( this, name, group );
	}
};