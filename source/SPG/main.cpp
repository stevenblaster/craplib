#include "precompiled.h"

#include "opengl/renderwindow.h"
#include "opengl/setup.h"
#include "opengl/keyboard.h"
#include "opengl/mouse.h"
#include "opengl/buffer.h"


#include "math/vector3.h"
#include "math/vector2.h"

// temporary until jean luc is done
#if defined( CRAP_PLATFORM_WIN )
#include <gl/GL.h>
#include <gl/GLU.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "contentmanager.h"
#include "geometrycontent.h"
#include "texturecontent.h"
#include "shadercontent.h"
#include "shadermanager.h"

#include "vbo.h"
#include "tbo.h"
#include "sbo.h"

#include "camera.h"

//math stuff yet done with glm
#include "glm/glm.hpp"
#include "glm/ext.hpp"

void handleInput(crap::keyboard& keyboard, crap::mouse& mouse, camera& cam);
crap::vector2i mouse_pos;

int main( void )
{
	//setup window
	crap::window_setup win_setup;
	win_setup.title = "Funny Window";
	win_setup.width = 1024;
	win_setup.height = 768;
	win_setup.multisampling_count = 8;
	win_setup.opengl_version = 3.3f;
    win_setup.opengl_profile = crap::compat;

	//create window
	crap::window window( win_setup );
	window.open();

	//get keyboard and mouse
	crap::keyboard keyboard;
	crap::mouse mouse;

	// temporary
	crap::opengl::enable(crap::opengl::depth_test);
	crap::opengl::setDepthComparison(crap::opengl::less);
	crap::opengl::enable(crap::opengl::cull_face);

	//create contentmanager
	content_manager cm;
	cm.init( "spg.ini" );

	//create vertex array
	crap::vertex_array vert_array;
	vert_array.bind();

	//test: load vbo onto GPU
	vbo cube_vbo( "cube", &cm, vbo::static_draw );

	geometry_content ig;
	cm.create_content( "cube" , &ig, type_name::geometry );

	//test: load texture onto GPU
	tbo diffuse_tbo( "flower_diff", &cm, tbo::tga );
	tbo normal_tbo( "flower_norm", &cm, tbo::tga );

	//test: load linked shader progam onto GPU
	shader_manager sm(&cm);
	sm.add("crap_vert", "crap_frag");
	sm.set_current("crap_vert", "crap_frag");

	//get stuff from shader program
	crap::uniform MatrixID = sm.current()->uniform_location("world_matrix");
	crap::uniform ViewMatrixID = sm.current()->uniform_location("view_matrix");
	crap::uniform ModelMatrixID = sm.current()->uniform_location("model_matrix");
	crap::uniform ModelView3x3MatrixID = sm.current()->uniform_location("model_view_matrix");
	crap::uniform DiffuseTextureID  = sm.current()->uniform_location("diffuse_texture");
	crap::uniform NormalTextureID  = sm.current()->uniform_location("normal_texture");
	crap::uniform LightType1ID = sm.current()->uniform_location("lightType1");
	crap::uniform LightType2ID = sm.current()->uniform_location("lightType2");
	crap::uniform LightType3ID = sm.current()->uniform_location("lightType3");
	crap::uniform SpecTypeID = sm.current()->uniform_location("specType");
	crap::uniform BumpID = sm.current()->uniform_location("bumpEnabled");

	// setup camera
	camera cam;
	cam.lookat(
				glm::vec3( 5.0f, 0.0f, 0.0f ),
				glm::vec3( 0.0f, 0.0f, 0.0f ),
				glm::vec3( 0.0f, 1.0f, 0.0f )
				);
	mouse_pos = mouse.position();

	// Projection matrix : 60° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 ProjectionMatrix = glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// setup cube coordinates
	glm::mat4 ModelMatrix(1.0f);
	glm::mat4 ModelViewMatrix(1.0f);
	// get view matrix
	glm::mat4 ViewMatrix = cam.get_view();
	// model view projection matrix
	glm::mat4 MVP(1.0f);
	glm::mat3 ModelView3x3Matrix(1.0f);

	// temporary
	crap::opengl::clearColor(1.0f, 1.0f, 1.0f, 0.0f);

	int lightType[] = {0, 0, 0};
	int specType[] = {0, 0, 0};
	int bump[] = {0, 0, 0};

	int activeComponent = 0;

	while( !keyboard.is_pressed( crap::keyboard::key_escape ) && window.is_open() && !mouse.is_pressed(crap::mouse::button_1) )
	{
		crap::opengl::clear(crap::opengl::color_depth_buffer);

		// update positions
		handleInput(keyboard, mouse, cam);

		ViewMatrix = cam.get_view();
		ModelViewMatrix = ViewMatrix * ModelMatrix;
		ModelView3x3Matrix = glm::mat3(ModelViewMatrix);
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		//activate shader program and connect data
		sm.activate();
		sm.current()->uniform_matrix4f_value( MatrixID, 1, &MVP[0][0]);
		sm.current()->uniform_matrix4f_value( ModelMatrixID, 1, &ModelMatrix[0][0]);
		sm.current()->uniform_matrix4f_value( ViewMatrixID, 1, &ViewMatrix[0][0]);
		sm.current()->uniform_matrix4f_value( ModelView3x3MatrixID, 1, &ModelView3x3Matrix[0][0]);
		sm.current()->uniform_1i( LightType1ID, lightType[0]);
		sm.current()->uniform_1i( LightType2ID, lightType[1]);
		sm.current()->uniform_1i( LightType3ID, lightType[2]);
		sm.current()->uniform_1i( SpecTypeID, specType[0]);
		sm.current()->uniform_1i( BumpID, bump[0] );

		sm.activate();

		//activate texture buffer and connect data
		diffuse_tbo.activate();
		diffuse_tbo.bind_buffer();
		sm.current()->uniform_1i( DiffuseTextureID, 0);

		normal_tbo.activate();
		normal_tbo.bind_buffer();
		sm.current()->uniform_1i( NormalTextureID, 1);

		//define data of buffers
		sm.current()->vertex_attribute_array.enable(0);
		cube_vbo.bind_buffer( vbo::verticies );
		sm.current()->vertex_attribute_array.pointer( 0, 3, crap::gl_float, false, 0, (void*)0);

		sm.current()->vertex_attribute_array.enable(1);
		cube_vbo.bind_buffer( vbo::uvs );
		sm.current()->vertex_attribute_array.pointer( 1, 2, crap::gl_float, false, 0, (void*)0);

		sm.current()->vertex_attribute_array.enable(2);
		cube_vbo.bind_buffer( vbo::normals );
		sm.current()->vertex_attribute_array.pointer( 2, 3, crap::gl_float, false, 0, (void*)0);

		sm.current()->vertex_attribute_array.enable(3);
		cube_vbo.bind_buffer( vbo::tangents );
		sm.current()->vertex_attribute_array.pointer( 3, 3, crap::gl_float, false, 0, (void*)0);

		sm.current()->vertex_attribute_array.enable(4);
		cube_vbo.bind_buffer( vbo::binormals );
		sm.current()->vertex_attribute_array.pointer( 4, 3, crap::gl_float, false, 0, (void*)0);

		//draw the fuck
		cube_vbo.bind_buffer( vbo::indicies );
		crap::opengl::draw_elements(
			crap::opengl::triangles,		// mode
			cube_vbo.indicies_size,			// count
			crap::opengl::unsigned_short	// type
		);

		//disable data define stuff
		sm.current()->vertex_attribute_array.disable(0);
		sm.current()->vertex_attribute_array.disable(1);
		sm.current()->vertex_attribute_array.disable(2);
		sm.current()->vertex_attribute_array.disable(3);
		sm.current()->vertex_attribute_array.disable(4);


		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf((const GLfloat*)&ProjectionMatrix[0]);
		glMatrixMode(GL_MODELVIEW);
		glm::mat4 MV = ViewMatrix * ModelMatrix;
		glLoadMatrixf((const GLfloat*)&MV[0]);


		sm.activate();

		// normals
		glColor3f(0,0,1);
		glBegin(GL_LINES);
		for (unsigned int i=0; i<ig.indices_size; i++){
			glm::vec3 p = glm::vec3(ig.positions[ig.indices[i]].x, ig.positions[ig.indices[i]].y, ig.positions[ig.indices[i]].z );
			glVertex3fv(&p.x);
			glm::vec3 o = glm::normalize( glm::vec3(ig.normals[ig.indices[i]].x, ig.normals[ig.indices[i]].y, ig.normals[ig.indices[i]].z)  );
			p+=o*0.1f;
			glVertex3fv(&p.x);
		}
		glEnd();
		// tangents
		glColor3f(1,0,0);
		glBegin(GL_LINES);
		for (unsigned int i=0; i<ig.indices_size; i++){
			glm::vec3 p = glm::vec3(ig.positions[ig.indices[i]].x, ig.positions[ig.indices[i]].y, ig.positions[ig.indices[i]].z );
			glVertex3fv(&p.x);
			glm::vec3 o = glm::normalize( glm::vec3(ig.tangents[ig.indices[i]].x, ig.tangents[ig.indices[i]].y, ig.tangents[ig.indices[i]].z)  );
			p+=o*0.1f;
			glVertex3fv(&p.x);
		}
		glEnd();

		// bitangents
		glColor3f(0,1,0);
		glBegin(GL_LINES);
		for (unsigned int i=0; i<ig.indices_size; i++){
			glm::vec3 p = glm::vec3(ig.positions[ig.indices[i]].x, ig.positions[ig.indices[i]].y, ig.positions[ig.indices[i]].z );
			glVertex3fv(&p.x);
			glm::vec3 o = glm::normalize( glm::vec3(ig.binormals[ig.indices[i]].x, ig.binormals[ig.indices[i]].y, ig.binormals[ig.indices[i]].z)  );
			p+=o*0.1f;
			glVertex3fv(&p.x);
		}
		glEnd();

		glm::vec3 debug_light;

		// light pos 1
		glColor3f(1,1,1);
		glBegin(GL_LINES);
			debug_light = glm::vec3( 0.0f,  1.0f,  2.0f );
			glVertex3fv(&debug_light.x);
			debug_light+=glm::vec3(1,0,0)*0.1f;
			glVertex3fv(&debug_light.x);
			debug_light-=glm::vec3(1,0,0)*0.1f;
			glVertex3fv(&debug_light.x);
			debug_light+=glm::vec3(0,1,0)*0.1f;
			glVertex3fv(&debug_light.x);
		glEnd();


		//poll and swap
		window.swap();
		window.poll_events();

		if( keyboard.is_pressed( crap::keyboard::key_C ) )
		{
			//if( sm.is_current("crop_vert", "crop_frag") )
			//	//sm.set_current("vertex_texture_only", "fragment_texture_only");
			//else
			//	sm.set_current("crop_vert", "crop_frag");
		}

		if( keyboard.is_pressed( crap::keyboard::key_1 ) )
			activeComponent = 1;
		else if( keyboard.is_pressed(  crap::keyboard::key_2 ) )
			activeComponent = 2;
		else if( keyboard.is_pressed(  crap::keyboard::key_3 ) )
			activeComponent = 3;
		else if( keyboard.is_pressed(  crap::keyboard::key_4 ) )
			activeComponent = 4;
		else if( keyboard.is_pressed(  crap::keyboard::key_5 ) )
			activeComponent = 5;
		else if( keyboard.is_pressed(  crap::keyboard::key_6 ) )
			activeComponent = 6;

		if( activeComponent < 4)
		{
			if( keyboard.is_pressed( crap::keyboard::key_p ) )
			{
				lightType[activeComponent - 1] = ( lightType[activeComponent - 1] + 1 ) % 3;
			}
		}
		else
		{
			if( keyboard.is_pressed( crap::keyboard::key_s ) )
			{
				specType[activeComponent - 4] = ( specType[activeComponent - 4] + 1 ) % 3;
			}
			if( keyboard.is_pressed( crap::keyboard::key_b ) )
			{
				bump[activeComponent - 4] = ( bump[activeComponent - 4] + 1 ) % 2;
			}
		}
	}

	//geometry_content ig;
	//cm.create_content( "ape" , &ig, type_name::geometry );

	//texture_content tc;
	//cm.create_content( "color", &tc, type_name::texture );

	//shader_content sc;
	//cm.create_content( "fragment_texture_only", &sc, type_name::shader );

	//cm.save_content( "fragment_texture_only", &sc, type_name::shader );
	return 0;
}

void handleInput(crap::keyboard& keyboard, crap::mouse& mouse, camera& cam)
{
	if( keyboard.is_pressed(crap::keyboard::key_W) || keyboard.is_pressed(crap::keyboard::key_w))
		cam.forward();
	if( keyboard.is_pressed(crap::keyboard::key_S) || keyboard.is_pressed(crap::keyboard::key_s))
		cam.backward();
	if( keyboard.is_pressed(crap::keyboard::key_A) || keyboard.is_pressed(crap::keyboard::key_a))
		cam.left();
	if( keyboard.is_pressed(crap::keyboard::key_D) || keyboard.is_pressed(crap::keyboard::key_D))
		cam.right();
	if( keyboard.is_pressed(crap::keyboard::key_up) || keyboard.is_pressed(crap::keyboard::key_page_up))
		cam.up();
	if( keyboard.is_pressed(crap::keyboard::key_down) || keyboard.is_pressed(crap::keyboard::key_page_down))
		cam.down();

	crap::vector2i mouse_position = mouse.position();
	crap::vector2i screensize( 1024, 768 );
	crap::vector2i screencenter = screensize / 2;

	cam.turn(glm::vec3( (mouse_position.x - screencenter.x)/2, (mouse_position.y - screencenter.y)/2, 0 ));

	mouse.set_position( screencenter );
	mouse.movement();

}