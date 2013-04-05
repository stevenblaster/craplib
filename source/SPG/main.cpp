#include "precompiled.h"

#if defined( CRAP_PLATFORM_WIN )
#include <gl/GL.h>
#include <gl/GLU.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "opengl/renderwindow.h"
#include "opengl/keyboard.h"
#include "opengl/mouse.h"

#include "opengl/buffer.h"

#include "contentmanager.h"
#include "geometrycontent.h"
#include "texturecontent.h"
#include "shadercontent.h"

#include "vbo.h"
#include "tbo.h"
#include "sbo.h"

int main( void )
{
	//setup window
	crap::window_setup win_setup;
	win_setup.title = "Funny Window";
	win_setup.width = 1024;
	win_setup.height = 768;
	win_setup.multisampling_count = 8;
	win_setup.opengl_version = 3.3f;
    win_setup.opengl_profile = crap::core;

	//create window
	crap::window window( win_setup );
	window.open();

	//get keyboard and mouse
	crap::keyboard keyboard;
	crap::mouse mouse;

	//create contentmanager
	content_manager cm;
	cm.init( "spg.ini" );

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	crap::vertex_array vert_array;
	vert_array.bind();

	//test: load vbo onto GPU
	vbo cube_vbo( "cube", &cm, vbo::static_draw );

	//test: load texture onto GPU
	tbo cube_tbo( "color", &cm, tbo::tga );

	//test: load linked shader progam onto GPU
	sbo cube_sbo( "vertex_ck", "fragment_ck", &cm );

	//while( !keyboard.is_pressed( crap::keyboard::key_escape ) && window.is_open() && !mouse.is_pressed(crap::mouse::button_1) )
	//{

	//}

	geometry_content ig;
	cm.create_content( "ape" , &ig, type_name::geometry );

	texture_content tc;
	cm.create_content( "color", &tc, type_name::texture );

	shader_content sc;
	cm.create_content( "fragment_texture_only", &sc, type_name::shader );

	//cm.save_content( "fragment_texture_only", &sc, type_name::shader );
	return 0;
}