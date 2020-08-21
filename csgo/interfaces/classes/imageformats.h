#pragma once

/* includes */
#include <stdio.h>

// don't bitch that inline functions aren't used!
#pragma warning(disable : 4514)

/* enums */
enum image_format {
	image_format_unknown = -1,
	image_format_rgba8888 = 0,
	image_format_abgr8888,
	image_format_rgb888,
	image_format_bgr888,
	image_format_rgb565,
	image_format_i8,
	image_format_ia88,
	image_format_p8,
	image_format_a8,
	image_format_rgb888_bluescreen,
	image_format_bgr888_bluescreen,
	image_format_argb8888,
	image_format_bgra8888,
	image_format_dxt1,
	image_format_dxt3,
	image_format_dxt5,
	image_format_bgrx8888,
	image_format_bgr565,
	image_format_bgrx5551,
	image_format_bgra4444,
	image_format_dxt1_onebitalpha,
	image_format_bgra5551,
	image_format_uv88,
	image_format_uvwq8888,
	image_format_rgba16161616f,
	image_format_rgba16161616,
	image_format_uvlx8888,
	image_format_r32f,
	image_format_rgb323232f,
	image_format_rgba32323232f,
	image_format_nv_dst16,
	image_format_nv_dst24,
	image_format_nv_intz,
	image_format_nv_rawz,
	image_format_ati_dst16,
	image_format_ati_dst24,
	image_format_nv_null,
	image_format_ati2n,
	image_format_ati1n,
	image_format_dxt1_runtime,
	image_format_dxt5_runtime,
	num_image_formats
};