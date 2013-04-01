#include "crap.h"
#include "opengl/openglwindow.h"
#include "opengl/opengldata.h"
#include "opengl/openglkeyboard.h"
#include "opengl/openglmouse.h"
#include "opengl/opengljoystick.h"
#include "opengl/openglshader.h"
#include "opengl/opengltexture.h"
#include "opengl/openglvertex.h"
#include "opengl/openglvbo.h"
#include "audio/audiodevice.h"
#include "files/file.h"
#include "math/vector3.h"
#include "audio/wavefile.h"
#include "opengl/wavefrontfile.h"
#include "control/logger.h"
#include "control/craptime.h"
#include "math/geometry.h"
#include "math/basemath.h"

#if defined( CRAP_PLATFORM_WIN )
#include <gl/GL.h>
#include <gl/GLU.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "glm/glm.hpp"
#include "glm/ext.hpp"

glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

void computeMatricesFromInputs( crap::opengl_keyboard& keyboard, crap::opengl_mouse& mouse );

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;

int main()
{
	typedef crap::logger<crap::filter_policy::no_filter_policy,crap::format_policy::simple_format_policy,crap::writer_policy::console_writer_policy> ConsoleLogger;
	ConsoleLogger c;
	CRAP_LOG_INFO(crap::log_channel::log_opengl,"OpenGL-Test Startup.");

	crap::opengl::window_setup setup;
	setup.title = "Funny Window";
	setup.width = 1024;
	setup.height = 768;
	setup.multisampling_count = 8;
	setup.opengl_version = 3.3f;
	setup.opengl_profile = crap::opengl::profile::core;

    crap::opengl::window window( setup );
	window.open();

	crap::opengl_keyboard keyboard;
	crap::opengl_mouse mouse;
	crap::opengl_joystick joy;

	crap::audiodevice audio_device;
	crap::wave_file wav( "audiofile.wav" );

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	crap::opengl::vertex_array vert_array = crap::opengl::vertex_array();
	vert_array.bind();

	crap::wavefront_file obj( "suzanne.obj" );

	crap::opengl::simple_vbo vbo;
	obj.generate_simple_vbo( &vbo );

	crap::opengl::program shader = crap::opengl::shader::link(
		crap::opengl::shader::compile( "vertexshader_ape.vs", crap::opengl::vertex_shader ),
		crap::opengl::shader::compile( "fragmentshader_ape.ps", crap::opengl::fragment_shader ), 0
		//crap::opengl::shader::compile( "geometryshader.gs", crap::opengl::geometry_shader )
	);


	// Get a handle for our uniforms in shader
	crap::opengl::uniform MatrixID = shader.uniform_location("MVP");
	crap::opengl::uniform ViewMatrixID = shader.uniform_location("V");
	crap::opengl::uniform ModelMatrixID = shader.uniform_location("M");
	crap::opengl::uniform TextureID = shader.uniform_location("myTextureSampler");
	crap::opengl::uniform LightID = shader.uniform_location("LightPosition_worldspace");

	//load texture
	crap::opengl::texture tex = crap::opengl::create_texture( "uvmap2.tga", crap::opengl::tga );

	//setup buffers
	crap::opengl::buffer vertex_buffer( crap::opengl::array_buffer, crap::opengl::static_draw );
	vertex_buffer.bind();
	vertex_buffer.set_data( vbo.vertices_size*3*sizeof(crap::vector3f), &vbo.positions[0] );

	crap::opengl::buffer uv_buffer( crap::opengl::array_buffer, crap::opengl::static_draw );
	uv_buffer.bind();
	uv_buffer.set_data( vbo.vertices_size *3*sizeof(crap::vector2f), &vbo.uvs[0] );

	crap::opengl::buffer normal_buffer( crap::opengl::array_buffer, crap::opengl::static_draw );
	normal_buffer.bind();
	normal_buffer.set_data( vbo.vertices_size *3*sizeof(crap::vector3f), &vbo.normals[0] );

	crap::opengl::buffer element_buffer( crap::opengl::element_array_buffer, crap::opengl::static_draw );
	element_buffer.bind();
	element_buffer.set_data( vbo.index_size *sizeof(u16), &vbo.indices[0] );

	//play sound
	wav.play( crap::vector3f(0,0,0), crap::vector3f(0,0,0), crap::vector3f(0,0,0), crap::vector3f(0,0,0),
		crap::vector3f(0,0,-1), crap::vector3f(0,1,0) );

	//loop
	while( !keyboard.is_pressed( crap::opengl_keyboard::key_escape ) && window.is_open() && !mouse.is_pressed(crap::opengl_mouse::button_1) )
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
        shader.activate();

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs(keyboard, mouse);
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		shader.uniform_matrix4f_value( MatrixID, 1, &MVP[0][0]);
		shader.uniform_matrix4f_value( ModelMatrixID, 1, &ModelMatrix[0][0]);
		shader.uniform_matrix4f_value( ViewMatrixID, 1, &ViewMatrix[0][0]);

		glm::vec3 lightPos = glm::vec3(4,4,4);
		shader.uniform_3f( LightID, lightPos.x, lightPos.y, lightPos.z);

		// Bind our texture in Texture Unit 0
		tex.activate();
		tex.bind();
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		shader.uniform_1i( TextureID, 0);

        // 1rst attribute buffer : vertices
		shader.vertex_attribute_array.enable(0);
		vertex_buffer.bind();
		shader.vertex_attribute_array.pointer( 0, 3, crap::opengl::gl_float, false, 0, (void*)0);

        // 2nd attribute buffer : colors
        shader.vertex_attribute_array.enable(1);
		uv_buffer.bind();
		shader.vertex_attribute_array.pointer( 1, 2, crap::opengl::gl_float, false, 0, (void*)0);

		// 3rd attribute buffer : normals
        shader.vertex_attribute_array.enable(2);
		normal_buffer.bind();
		shader.vertex_attribute_array.pointer( 2, 3, crap::opengl::gl_float, false, 0, (void*)0);

		// 4th run elemt fun
		glDrawElements(
			GL_TRIANGLES,      // mode
			vbo.index_size,    // count
			GL_UNSIGNED_SHORT,   // type
			(void*)0           // element array buffer offset
		);

		shader.vertex_attribute_array.disable(0);
		shader.vertex_attribute_array.disable(1);
		shader.vertex_attribute_array.disable(2);

		window.swap();
		window.poll_events();
		joy.poll_events();
	}
}

//controls
glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}
// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 5 ); 

// Initial horizontal angle : toward -Z
f32 horizontalAngle = 0.94f;

// Initial vertical angle : none
f32 verticalAngle = 0.f;

// Initial Field of View
f32 initialFoV = 45.0f;

void computeMatricesFromInputs( crap::opengl_keyboard& keyboard, crap::opengl_mouse& mouse ){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = ((double) crap::time::current_tick()) / crap::time::TICKS_PER_SECOND;

	// Compute time difference between current and last frame
	double currentTime = ((double)  crap::time::current_tick()) / crap::time::TICKS_PER_SECOND;
	float deltaTime = float(currentTime - lastTime);

	// Compute new orientation
	horizontalAngle += mouseSpeed * mouse.movement().x;
	verticalAngle   += mouseSpeed * mouse.movement().y;

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

	// Move forward
	if (keyboard.is_pressed( crap::opengl_keyboard::key_up )){
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (keyboard.is_pressed( crap::opengl_keyboard::key_down )){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (keyboard.is_pressed( crap::opengl_keyboard::key_right )){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (keyboard.is_pressed( crap::opengl_keyboard::key_left )){
		position -= right * deltaTime * speed;
	}

	float FoV = initialFoV - 5 *  mouse.wheel();// glfwGetMouseWheel();

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}