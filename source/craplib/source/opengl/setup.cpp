////////////////////////////////////////////////////////
// CRAP Library
//!		@file setup.cpp
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

#include "crap.h"
#include "math/vector4.h"

#if defined( CRAP_PLATFORM_WIN )
#include <gl/GL.h>
#include <gl/GLU.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif


#include "opengl/setup.h"

namespace crap
{
	namespace opengl
	{
		void enable(graphics_settings id)
		{
			i32 ogl_settings[]= {GL_BLEND, GL_COLOR_LOGIC_OP, GL_CULL_FACE,
					GL_DEPTH_TEST, GL_DITHER, GL_LINE_SMOOTH, GL_POLYGON_SMOOTH, 
					GL_POLYGON_OFFSET_FILL, GL_POLYGON_OFFSET_LINE, GL_POLYGON_OFFSET_POINT, 
					GL_POLYGON_SMOOTH, GL_SCISSOR_TEST, GL_STENCIL_TEST};
					/* .. continue .. */
			glEnable(ogl_settings[id]);
		}

		void disable(graphics_settings id)
		{
			i32 ogl_settings[]= {GL_BLEND, GL_COLOR_LOGIC_OP, GL_CULL_FACE,
				GL_DEPTH_TEST, GL_DITHER, GL_LINE_SMOOTH, GL_POLYGON_SMOOTH, 
				GL_POLYGON_OFFSET_FILL, GL_POLYGON_OFFSET_LINE, GL_POLYGON_OFFSET_POINT, 
				GL_POLYGON_SMOOTH, GL_SCISSOR_TEST, GL_STENCIL_TEST};
			/* .. continue .. */
			glDisable(ogl_settings[id]);
		}

		void clear(buffer_bits id)
		{
			i32 buffer_bits[] = {GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT, 
				GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT, GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT,
				GL_STENCIL_BUFFER_BIT|GL_DEPTH_BUFFER_BIT, 
				GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT|GL_DEPTH_BUFFER_BIT
			};
			glClear(buffer_bits[id]);
		}

		void clearColor(vector4f color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void clearColor(float r, float g, float b, float a)
		{
			glClearColor(r, g, b, a);
		}

		void setDepthComparison(depth_comparison id)
		{
			i32 depth_settings[] = { GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL,
				GL_GREATER, GL_NOTEQUAL, GL_GEQUAL, GL_ALWAYS };
			glDepthFunc(depth_settings[id]);			
		}

		void draw_elements(draw_mode draw_mode_id, size_t32 count, buffer_type buffer_type_id, void* offset)
		{
			i32 draw_modes[] = { GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP,
				GL_LINES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES};
			i32 buffer_modes[] = {GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT};

			glDrawElements(draw_modes[draw_mode_id], count, buffer_modes[buffer_type_id], offset);
		}
	}

}