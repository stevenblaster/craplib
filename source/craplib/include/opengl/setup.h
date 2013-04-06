////////////////////////////////////////////////////////
// CRAP Library
//!		@file setup.h
//
//	Author(s):
//! 	@author Johnny Beluga <kiepmad@gmail.com>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Johnny Beluga
//
//	Description:
//!		@brief wrapper for opengl settings
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_SETUP_H
#define CRAP_SETUP_H


namespace crap 
{
	namespace opengl
	{

		// please consider checking out the openGL documentation for an overview 
		// of these options: http://www.opengl.org/sdk/docs/man3/xhtml/glEnable.xml
		enum graphics_settings
		{
			blend = 0,
			color_logic_op,
			cull_face,
			depth_test,
			dither,
			smooth_line,
			polygon_offset_fill,
			polygon_offset_line,
			polygon_offset_point,
			polygon_smooth,
			primitive_restart,
			scissor_test,
			stencil_test,
			texture_cube_map_seamless,
		};

		enum depth_comparison 
		{
			never = 0,
			less,
			equal,
			lequal,
			greater,
			notequal,
			qequal,
			always
		};

		enum buffer_bits 
		{
			colorbuffer = 0,
			depthbuffer,
			stencilbuffer,
			color_depth_buffer,
			color_stencil_buffer,
			depth_stencil_buffer,
			color_depth_stencilbuffer
		};

		void enable(graphics_settings id);
		void disable(graphics_settings id);

		void clear(buffer_bits id);

		void clearColor(vector4f color);
		void clearColor(float red, float green, float blue, float alpha);

		void setDepthComparison(depth_comparison id);

	}
}

#endif //CRAP_SETUP_H