#include "crap.h"
#include "opengl/openglwindow.h"
#include "opengl/opengldata.h"
#include "opengl/openglkeyboard.h"
#include "opengl/openglmouse.h"
#include "opengl/opengljoystick.h"
#include "opengl/openglshader.h"
#include "opengl/opengltexture.h"
#include "audio/audiodevice.h"
#include "files/file.h"
#include "math/vector3.h"
#include "audio/wavefile.h"
#include "opengl/wavefrontfile.h"

#if defined( CRAP_PLATFORM_WIN )
#include <gl/GL.h>
#include <gl/GLU.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "glm/glm.hpp"
#include "glm/ext.hpp"

int main()
{
<<<<<<< HEAD
	ConsoleLogger c;
	CRAP_LOG_INFO(crap::log_channel::log_opengl,"OpenGL-Test Startup.");
=======
>>>>>>> 819b3a395d5e9b5227723792d5e1f450d91f3470
	crap::window_setup setup;
	setup.title = "Funny Window";
	setup.width = 1024;
	setup.height = 768;
	setup.multisampling_count = 8;
	setup.opengl_version = 3.3f;
	setup.opengl_profile = 0x00050001;

    crap::opengl_window window( setup );
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

	crap::wavefront_file obj( "cube.obj" );
	crap::vector3f* vertices = new crap::vector3f[ obj.face_index() * 3];
	crap::vector2f* uvs = new crap::vector2f[ obj.face_index() * 3];
	crap::vector3f* normals = new crap::vector3f[ obj.face_index() * 3];
	obj.generate_triangles( vertices, uvs, normals );

	crap::opengl::program shader = crap::opengl::shader::link(
		crap::opengl::shader::compile( "vertexshader_cube.vs", crap::opengl::vertex_shader ),
		crap::opengl::shader::compile( "fragmentshader_cube.ps", crap::opengl::fragment_shader ), 0
		//crap::opengl::shader::compile( "geometryshader.gs", crap::opengl::geometry_shader )
	);


	// Get a handle for our "MVP" uniform
	crap::opengl::uniform MatrixID = shader.uniform_location("MVP");

	//crap::opengl::texture tex = crap::opengl::create_texture( "uvtemplate.tga", crap::opengl::tga ); //doesnt work
	crap::opengl::texture tex = crap::opengl::create_texture_tga( "uvmap.tga" );
	tex._index = 0x84C0;

	crap::opengl::uniform TextureID = shader.uniform_location("myTextureSampler");

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    
	// Camera matrix
    glm::mat4 View       = glm::lookAt(
                glm::vec3(4,3,-3), // Camera is at (4,3,-3), in World Space
                glm::vec3(0,0,0), // and looks at the origin
                glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    
	// Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model      = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

	crap::opengl::buffer vertex_buffer( crap::opengl::array_buffer, crap::opengl::static_draw );
	vertex_buffer.bind();
	//vertex_buffer.set_data( sizeof(g_vertex_buffer_data), (void*)g_vertex_buffer_data );
	vertex_buffer.set_data( obj.face_index()*3*sizeof(crap::vector3f), &vertices[0] );

	//crap::opengl::buffer color_buffer( crap::opengl::array_buffer, crap::opengl::static_draw );
	//color_buffer.bind();
	//color_buffer.set_data( sizeof(g_color_buffer_data), (void*)g_color_buffer_data );

	crap::opengl::buffer uv_buffer( crap::opengl::array_buffer, crap::opengl::static_draw );
	uv_buffer.bind();
	//uv_buffer.set_data( sizeof(g_uv_buffer_data), (void*)g_uv_buffer_data );
	uv_buffer.set_data( obj.face_index()*3*sizeof(crap::vector2f), &uvs[0] );

	wav.play( crap::vector3f(0,0,0), crap::vector3f(0,0,0), crap::vector3f(0,0,0), crap::vector3f(0,0,0),
		crap::vector3f(0,0,-1), crap::vector3f(0,1,0) );

	while( !keyboard.is_pressed( crap::opengl_keyboard::key_escape ) && window.is_open() && !mouse.is_pressed(crap::opengl_mouse::button_1) )
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
        shader.activate();

        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
		shader.uniform_matrix4f_value( MatrixID, 1, &MVP[0][0]);

		// Bind our texture in Texture Unit 0
		tex.activate();
		tex.bind();
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		shader.uniform_1i( TextureID, 0);

        // 1rst attribute buffer : vertices
		shader.vertex_attribute_array.enable(0);
		vertex_buffer.bind();
		shader.vertex_attribute_array.pointer( 0, 3, false, 0, (void*)0);

        // 2nd attribute buffer : colors
        shader.vertex_attribute_array.enable(1);
		uv_buffer.bind();
		shader.vertex_attribute_array.pointer( 1, 2, false, 0, (void*)0);

        // Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, obj.face_index()*3);

		shader.vertex_attribute_array.disable(0);
		shader.vertex_attribute_array.disable(1);

		window.swap();
		window.poll_events();
		joy.poll_events();
	}
}
