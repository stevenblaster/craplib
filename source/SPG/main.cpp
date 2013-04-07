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
	//cm.save_content( "cube", &ig, type_name::geometry );

	//test: load texture onto GPU
	tbo diffuse_tbo( "flower_diff", &cm, tbo::tga );
	tbo normal_tbo( "flower_norm", &cm, tbo::tga );
	tbo specular_tbo( "flower_spec", &cm, tbo::tga );

	//test: load linked shader progam onto GPU
	//sbo cube_sbo( "vertex_texture_only", "fragment_texture_only", &cm );
	shader_manager sm(&cm);
	sm.add("crop_vert", "crop_frag");
	sm.add("vertex_texture_only", "fragment_texture_only");
	sm.set_current("crop_vert", "crop_frag");
	//sbo cube_sbo( "vertex_std", "fragment_std", &cm );

	//get stuff from shader program
	crap::uniform MatrixID = sm.current()->uniform_location("world_matrix");
	crap::uniform ViewMatrixID = sm.current()->uniform_location("view_matrix");
	crap::uniform ModelMatrixID = sm.current()->uniform_location("model_matrix");
	crap::uniform ModelView3x3MatrixID = sm.current()->uniform_location("model_view_matrix");
	crap::uniform TextureID  = sm.current()->uniform_location("myTextureSampler");
	crap::uniform DiffuseTextureID  = sm.current()->uniform_location("diffuse_texture");
	crap::uniform NormalTextureID  = sm.current()->uniform_location("normal_texture");
	crap::uniform SpecularTextureID  = sm.current()->uniform_location("specular_texture");
	crap::uniform AmbientColorID = sm.current()->uniform_location("ambient_color");

	//light 1
	crap::uniform SpecularTypeID1 = sm.current()->uniform_location("specular_type1");
	crap::uniform LightPositionID1 = sm.current()->uniform_location("light_position1");
	crap::uniform LightViewMatrixID1 = sm.current()->uniform_location("light_view_matrix1");
	crap::uniform LightTypeID1 = sm.current()->uniform_location("light_type1");
	crap::uniform LightColorID1 = sm.current()->uniform_location("light_color1");
	crap::uniform LightPowerID1 = sm.current()->uniform_location("light_power1");
	crap::uniform SpecularColorID1 = sm.current()->uniform_location("specular_color1");

	//light 2
	crap::uniform SpecularTypeID2 = sm.current()->uniform_location("specular_type2");
	crap::uniform LightPositionID2 = sm.current()->uniform_location("light_position2");
	crap::uniform LightViewMatrixID2 = sm.current()->uniform_location("light_view_matrix2");
	crap::uniform LightTypeID2 = sm.current()->uniform_location("light_type2");
	crap::uniform LightColorID2 = sm.current()->uniform_location("light_color2");
	crap::uniform LightPowerID2 = sm.current()->uniform_location("light_power2");
	crap::uniform SpecularColorID2 = sm.current()->uniform_location("specular_color2");

	//light 3
	crap::uniform SpecularTypeID3 = sm.current()->uniform_location("specular_type3");
	crap::uniform LightPositionID3 = sm.current()->uniform_location("light_position3");
	crap::uniform LightViewMatrixID3 = sm.current()->uniform_location("light_view_matrix3");
	crap::uniform LightTypeID3 = sm.current()->uniform_location("light_type3");
	crap::uniform LightColorID3 = sm.current()->uniform_location("light_color3");
	crap::uniform LightPowerID3 = sm.current()->uniform_location("light_power3");
	crap::uniform SpecularColorID3 = sm.current()->uniform_location("specular_color3");

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

	//light struct
	struct light
	{
		int lightType;
		glm::vec3 lightPos;
		glm::vec3 lightColor;
		float lightPower;
		glm::vec3 specularColor;
	};

	//3 lights
	glm::vec3 ambientColor = glm::vec3(0.1, 0.1, 0.1);
	light l1;
	light l2;
	light l3;

	//light 1
	l1.lightType = 1;
	l1.lightPos = glm::vec3(4,0,0);
	l1.lightColor = glm::vec3(1,1,1);
	l1.lightPower = 50.0f;
	l1.specularColor = glm::vec3(0.0f,0.0f,0.0f);

	//light 2
	l2.lightType = 0;
	l2.lightPos = glm::vec3(0,0,4);
	l2.lightColor = glm::vec3(1,1,1);
	l2.lightPower = 40.0f;
	l2.specularColor = glm::vec3(0.3f,0.0f,0.0f);

	//light 3
	l3.lightType = 0;
	l3.lightPos = glm::vec3(0,0,-4);
	l3.lightColor = glm::vec3(1,1,1);
	l3.lightPower = 40.0f;
	l3.specularColor = glm::vec3(0.0f,0.3f,0.0f);

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
		sm.current()->uniform_3f(AmbientColorID, ambientColor.x, ambientColor.y, ambientColor.z);

		//light 1
		sm.current()->uniform_1i(LightTypeID1, l1.lightType);
		sm.current()->uniform_3f(LightPositionID1, l1.lightPos.x, l1.lightPos.y, l1.lightPos.z);
		sm.current()->uniform_3f(LightColorID1, l1.lightColor.x, l1.lightColor.y, l1.lightColor.z);
		sm.current()->uniform_1f(LightPowerID1, l1.lightPower);
		sm.current()->uniform_3f(SpecularColorID1, l1.specularColor.x, l1.specularColor.y, l1.specularColor.z);

		//light 2
		sm.current()->uniform_1i(LightTypeID2, l2.lightType);
		sm.current()->uniform_3f(LightPositionID2, l2.lightPos.x, l2.lightPos.y, l2.lightPos.z);
		sm.current()->uniform_3f(LightColorID2, l2.lightColor.x, l2.lightColor.y, l2.lightColor.z);
		sm.current()->uniform_1f(LightPowerID2, l2.lightPower);
		sm.current()->uniform_3f(SpecularColorID2, l2.specularColor.x, l2.specularColor.y, l2.specularColor.z);

		//light 3
		sm.current()->uniform_1i(LightTypeID3, l3.lightType);
		sm.current()->uniform_3f(LightPositionID3, l3.lightPos.x, l3.lightPos.y, l3.lightPos.z);
		sm.current()->uniform_3f(LightColorID3, l3.lightColor.x, l3.lightColor.y, l3.lightColor.z);
		sm.current()->uniform_1f(LightPowerID3, l3.lightPower);
		sm.current()->uniform_3f(SpecularColorID3, l3.specularColor.x, l3.specularColor.y, l3.specularColor.z);

		//activate texture buffer and connect data
		diffuse_tbo.activate();
		diffuse_tbo.bind_buffer();
		sm.current()->uniform_1i( DiffuseTextureID, 0);

		normal_tbo.activate();
		normal_tbo.bind_buffer();
		sm.current()->uniform_1i( NormalTextureID, 1);

		specular_tbo.activate();
		specular_tbo.bind_buffer();
		sm.current()->uniform_1i( SpecularTextureID, 2);

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
<<<<<<< HEAD
		glColor3f(1,1,1);
		glBegin(GL_LINES);
			debug_light = l1.lightPos;
			glVertex3fv(&debug_light.x);
			debug_light+=glm::vec3(1,0,0)*0.1f;
			glVertex3fv(&debug_light.x);
			debug_light-=glm::vec3(1,0,0)*0.1f;
			glVertex3fv(&debug_light.x);
			debug_light+=glm::vec3(0,1,0)*0.1f;
			glVertex3fv(&debug_light.x);
		glEnd();

		// light pos 2
		glColor3f(1,1,1);
		glBegin(GL_LINES);
			debug_light = l2.lightPos;
			glVertex3fv(&debug_light.x);
			debug_light+=glm::vec3(1,0,0)*0.1f;
			glVertex3fv(&debug_light.x);
			debug_light-=glm::vec3(1,0,0)*0.1f;
			glVertex3fv(&debug_light.x);
			debug_light+=glm::vec3(0,1,0)*0.1f;
			glVertex3fv(&debug_light.x);
		glEnd();

		// light pos 3
		glColor3f(1,1,1);
		glBegin(GL_LINES);
=======
		glColor3f(1,1,1);
		glBegin(GL_LINES);
			debug_light = l1.lightPos;
			glVertex3fv(&debug_light.x);
			debug_light+=glm::vec3(1,0,0)*0.1f;
			glVertex3fv(&debug_light.x);
			debug_light-=glm::vec3(1,0,0)*0.1f;
			glVertex3fv(&debug_light.x);
			debug_light+=glm::vec3(0,1,0)*0.1f;
			glVertex3fv(&debug_light.x);
		glEnd();

		// light pos 2
		glColor3f(1,1,1);
		glBegin(GL_LINES);
			debug_light = l2.lightPos;
			glVertex3fv(&debug_light.x);
			debug_light+=glm::vec3(1,0,0)*0.1f;
			glVertex3fv(&debug_light.x);
			debug_light-=glm::vec3(1,0,0)*0.1f;
			glVertex3fv(&debug_light.x);
			debug_light+=glm::vec3(0,1,0)*0.1f;
			glVertex3fv(&debug_light.x);
		glEnd();

		// light pos 3
		glColor3f(1,1,1);
		glBegin(GL_LINES);
>>>>>>> cf6de15526dc1215b64c6e9c18704a31ef3e5fbb
			debug_light = l3.lightPos;
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
			if( sm.is_current("crop_vert", "crop_frag") )
				sm.set_current("vertex_texture_only", "fragment_texture_only");
			else
				sm.set_current("crop_vert", "crop_frag");
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
<<<<<<< HEAD
		cam.down();
=======

		cam.down();

	// FIXME: mouse rotation does not currently work!

	//crap::vector2i movement = mouse.movement();
	//if(movement.x > 0)
	//	cam.turnright();
	//else if(movement.x < 0)
	//	cam.turnleft();

	//if(movement.y > 0)
	//	cam.turnup();
	//else if(movement.y < 0)
	//	cam.turndown();

	//mouse.set_position(crap::vector2i(0,0));
	//mouse.movement();


		movement.y -= 0.01f;

	cam.move( movement.x, movement.y, movement.z );
>>>>>>> cf6de15526dc1215b64c6e9c18704a31ef3e5fbb

	crap::vector2i mouse_position = mouse.position();
	crap::vector2i screensize( 1024, 768 );
	crap::vector2i screencenter = screensize / 2;

	cam.turn(glm::vec3( (mouse_position.x - screencenter.x)/2, (mouse_position.y - screencenter.y)/2, 0 ));

	mouse.set_position( screencenter );
<<<<<<< HEAD
	mouse.movement();
=======

>>>>>>> cf6de15526dc1215b64c6e9c18704a31ef3e5fbb
}