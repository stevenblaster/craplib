#include "precompiled.h"

#include "opengl/renderwindow.h"
#include "opengl/setup.h"
#include "opengl/keyboard.h"
#include "opengl/mouse.h"
#include "opengl/buffer.h"

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

#include "vbo.h"
#include "tbo.h"
#include "sbo.h"

//math stuff yet done with glm
#include "glm/glm.hpp"
#include "glm/ext.hpp"

//also temp
glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}

void computeMatricesFromInputs();

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

	//test: load texture onto GPU
	tbo cube_tbo( "color", &cm, tbo::tga );
	//tbo normal_tbo( "specular", &cm, tbo::tga );

	//test: load linked shader progam onto GPU
	sbo cube_sbo( "vertex_texture_only", "fragment_texture_only", &cm );

	//get stuff from shader program
	crap::uniform MatrixID = cube_sbo->uniform_location("MVP");
	crap::uniform ViewMatrixID = cube_sbo->uniform_location("V");
	crap::uniform ModelMatrixID = cube_sbo->uniform_location("M");
	crap::uniform TextureID  = cube_sbo->uniform_location("myTextureSampler");
	crap::uniform LightID = cube_sbo->uniform_location("LightPosition_worldspace");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
								glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

	// temporary
	crap::opengl::clearColor(0.0f, 0.0f, 0.4f, 0.0f);

	while( !keyboard.is_pressed( crap::keyboard::key_escape ) && window.is_open() && !mouse.is_pressed(crap::mouse::button_1) )
	{
		//temporary
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		crap::opengl::clear(crap::opengl::color_depth_buffer);
		computeMatricesFromInputs();
		glm::mat4 ModelMatrix = glm::mat4(1.0);


		//activate shader porgram and connect data
		cube_sbo->activate();
		cube_sbo->uniform_matrix4f_value( MatrixID, 1, &MVP[0][0]);
		cube_sbo->uniform_matrix4f_value( ModelMatrixID, 1, &ModelMatrix[0][0]);
		cube_sbo->uniform_matrix4f_value( ViewMatrixID, 1, &ViewMatrix[0][0]);

		glm::vec3 lightPos = glm::vec3(4,4,4);
		cube_sbo->uniform_3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		//activate texture buffer and connect data
		cube_tbo.activate();
		cube_tbo.bind_buffer();
		cube_sbo->uniform_1i( TextureID, 0);

		//define data of buffers
		cube_sbo->vertex_attribute_array.enable(0);
		cube_vbo.bind_buffer( vbo::verticies );
		cube_sbo->vertex_attribute_array.pointer( 0, 3, crap::gl_float, false, 0, (void*)0);

		cube_sbo->vertex_attribute_array.enable(1);
		cube_vbo.bind_buffer( vbo::uvs );
		cube_sbo->vertex_attribute_array.pointer( 1, 2, crap::gl_float, false, 0, (void*)0);

		cube_sbo->vertex_attribute_array.enable(2);
		cube_vbo.bind_buffer( vbo::normals );
		cube_sbo->vertex_attribute_array.pointer( 2, 3, crap::gl_float, false, 0, (void*)0);

		//draw the fuck
		cube_vbo.bind_buffer( vbo::indicies );
		glDrawElements(
			GL_TRIANGLES,      // mode
			cube_vbo.indicies_size,    // count
			GL_UNSIGNED_SHORT,   // type
			(void*)0           // element array buffer offset
		);

		//disable data define stuff
		cube_sbo->vertex_attribute_array.disable(0);
		cube_sbo->vertex_attribute_array.disable(1);
		cube_sbo->vertex_attribute_array.disable(2);

		//poll and swap
		window.swap();
		window.poll_events();
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

void computeMatricesFromInputs(){

	// Compute new orientation
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	// Up vector
	glm::vec3 up = glm::cross( right, direction );


	float FoV = 45.0f;

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::vec3 position = glm::vec3( 0, 0, 5 ); 
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );
}