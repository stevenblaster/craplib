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

	//lights
	crap::uniform LightNumbersID = sm.current()->uniform_location("light_number");
	crap::uniform LightInfoArrayID = sm.current()->uniform_location("light_infos");
	

	//light uniforms

	crap::uniform uni_specular_type;
	crap::uniform uni_light_type;

	crap::uniform uni_light_position;
	crap::uniform uni_light_power;

	crap::uniform uni_specular_color;

	crap::uniform uni_camera_light_direction;
	crap::uniform uni_tangent_light_direction;


	int specular_type[3];
	int light_type[3];
	glm::vec3 light_position[3]; 
	float light_power[3];
	glm::vec3 specular_color[3];
	glm::vec3 camera_light_direction[3];
	glm::vec3 tangent_light_direction[3];

	i32 light_number = 2;
	//light 1
	specular_type[0] = 0;
	light_type[0] = 0;
	light_position[0] = glm::vec3(0,0,-4);
	light_power[0] = 30.f;
	specular_color[0] = glm::vec3(0,0,1);
	camera_light_direction[0] = glm::vec3(0,0,0);
	tangent_light_direction[0] = glm::vec3(0,0,0);

	specular_type[1] = 0;
	light_type[1] = 0;
	light_position[1] = glm::vec3(4,0,0);
	light_power[1] = 30.f;
	specular_color[1] = glm::vec3(1,0,0);
	camera_light_direction[1] = glm::vec3(0,0,0);
	tangent_light_direction[1] = glm::vec3(0,0,0);

	specular_type[2] = 0;
	light_type[2] = 0;
	light_position[2] = glm::vec3(4,4,4);
	light_power[2] = 30.f;
	specular_color[2] = glm::vec3(0,1,0);
	camera_light_direction[2] = glm::vec3(0,0,0);
	tangent_light_direction[2] = glm::vec3(0,0,0);

	uni_specular_type = sm.current()->uniform_location(	"start_specular_type");
	uni_light_type = sm.current()->uniform_location(	"start_light_type");
	uni_light_position = sm.current()->uniform_location("start_light_position");
	uni_light_power = sm.current()->uniform_location(	"start_light_power");
	uni_specular_color = sm.current()->uniform_location("start_specular_color");

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

	while( !keyboard.is_pressed( crap::keyboard::key_escape ) && window.is_open() && !mouse.is_pressed(crap::mouse::button_1) )
	{
		crap::opengl::clear(crap::opengl::color_depth_buffer);

		// update positions
		handleInput(keyboard, mouse, cam);

		ViewMatrix = cam.get_view();
		ModelViewMatrix = ViewMatrix * ModelMatrix;
		ModelView3x3Matrix = glm::mat3(ModelViewMatrix);
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		//activate shader porgram and connect data
		sm.activate();
		sm.current()->uniform_matrix4f_value( MatrixID, 1, &MVP[0][0]);
		sm.current()->uniform_matrix4f_value( ModelMatrixID, 1, &ModelMatrix[0][0]);
		sm.current()->uniform_matrix4f_value( ViewMatrixID, 1, &ViewMatrix[0][0]);
		sm.current()->uniform_matrix4f_value( ModelView3x3MatrixID, 1, &ModelView3x3Matrix[0][0]);

		//light
		sm.activate();
		sm.current()->uniform_1i(LightNumbersID, light_number);
		sm.current()->uniform_1i_value( uni_specular_type, 3, specular_type );
		sm.current()->uniform_1i_value( uni_light_type, 3, light_type );
		sm.current()->uniform_3f_value( uni_light_position, 3, (f32*)light_position );
		sm.current()->uniform_1f_value( uni_light_power, 3, light_power );
		sm.current()->uniform_3f_value( uni_specular_color, 3, (f32*)specular_color );

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
		//glColor3f(1,1,1);
		//glBegin(GL_LINES);
		//	debug_light = lights[0].light_position;
		//	glVertex3fv(&debug_light.x);
		//	debug_light+=glm::vec3(1,0,0)*0.1f;
		//	glVertex3fv(&debug_light.x);
		//	debug_light-=glm::vec3(1,0,0)*0.1f;
		//	glVertex3fv(&debug_light.x);
		//	debug_light+=glm::vec3(0,1,0)*0.1f;
		//	glVertex3fv(&debug_light.x);
		//glEnd();


		//poll and swap
		window.swap();
		window.poll_events();

		if( keyboard.is_pressed( crap::keyboard::key_1 ) )
		{
			light_number = 1;
		}
		if( keyboard.is_pressed( crap::keyboard::key_2 ) )
		{
			light_number = 2;
		}
		if( keyboard.is_pressed( crap::keyboard::key_3 ) )
		{
			light_number = 3;
		}

		if( keyboard.is_pressed( crap::keyboard::key_B ) )
		{
			specular_type[0] = 0;
		}

		if( keyboard.is_pressed( crap::keyboard::key_P ) )
		{
			specular_type[0] = 1;
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
	 glm::vec3 offset( 0.0f, 0.0f, 0.0f);
	 if( keyboard.is_pressed(crap::keyboard::key_W) || keyboard.is_pressed(crap::keyboard::key_w))
	  cam.offsetPosition( cam.forward() * 0.1f);
	 if( keyboard.is_pressed(crap::keyboard::key_S) || keyboard.is_pressed(crap::keyboard::key_s))
	  cam.offsetPosition( -cam.forward() * 0.1f);
	 if( keyboard.is_pressed(crap::keyboard::key_A) || keyboard.is_pressed(crap::keyboard::key_a))
	  cam.offsetPosition( -cam.right() * 0.1f);
	 if( keyboard.is_pressed(crap::keyboard::key_D) || keyboard.is_pressed(crap::keyboard::key_D))
	  cam.offsetPosition( cam.right() * 0.1f);
	 if( keyboard.is_pressed(crap::keyboard::key_up) || keyboard.is_pressed(crap::keyboard::key_page_up))
	  cam.offsetPosition( cam.up() * 0.1f);
	 if( keyboard.is_pressed(crap::keyboard::key_down) || keyboard.is_pressed(crap::keyboard::key_page_down))
	  cam.offsetPosition( -cam.up() * 0.1f);

	 crap::vector2i mouse_position = mouse.position();
	 crap::vector2i screensize( 1024, 768 );
	 crap::vector2i screencenter = screensize / 2;

	 crap::vector2i move = mouse.movement();
	 cam.offsetOrientation( move.y/10.0f, move.x/10.0f );
	 mouse.movement();

}