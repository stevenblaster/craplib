#include "crap.h"
#include "opengl/openglwindow.h"
#include "opengl/opengldata.h"
#include "opengl/openglkeyboard.h"
#include "opengl/openglmouse.h"
#include "opengl/opengljoystick.h"
#include "opengl/openglshader.h"
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
	crap::window_setup setup;
	setup.title = "Funny Window";
	setup.width = 1024;
	setup.height = 768;
	setup.multisampling_count = 8;
	setup.opengl_version = 3.3f;

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

	crap::opengl::vertex_array vert_array = crap::opengl::vertex_array();
	vert_array.bind();

	//crap::wavefront_file obj( "cube.obj" );

	crap::opengl::program shader = crap::opengl::shader::link(
		crap::opengl::shader::compile( "vertexshader.vs", crap::opengl::vertex_shader ),
		crap::opengl::shader::compile( "fragmentshader.ps", crap::opengl::fragment_shader ), 
		crap::opengl::shader::compile( "geometryshader.gs", crap::opengl::geometry_shader )
	);


	// Get a handle for our "MVP" uniform
	GLuint MatrixID = shader.uniform_location("MVP");

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

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
                -1.0f,-1.0f,-1.0f,
                -1.0f,-1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f,
                 1.0f, 1.0f,-1.0f,
                -1.0f,-1.0f,-1.0f,
                -1.0f, 1.0f,-1.0f,
                 1.0f,-1.0f, 1.0f,
                -1.0f,-1.0f,-1.0f,
                 1.0f,-1.0f,-1.0f,
                 1.0f, 1.0f,-1.0f,
                 1.0f,-1.0f,-1.0f,
                -1.0f,-1.0f,-1.0f,
                -1.0f,-1.0f,-1.0f,
                -1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f,-1.0f,
                 1.0f,-1.0f, 1.0f,
                -1.0f,-1.0f, 1.0f,
                -1.0f,-1.0f,-1.0f,
                -1.0f, 1.0f, 1.0f,
                -1.0f,-1.0f, 1.0f,
                 1.0f,-1.0f, 1.0f,
                 1.0f, 1.0f, 1.0f,
                 1.0f,-1.0f,-1.0f,
                 1.0f, 1.0f,-1.0f,
                 1.0f,-1.0f,-1.0f,
                 1.0f, 1.0f, 1.0f,
                 1.0f,-1.0f, 1.0f,
                 1.0f, 1.0f, 1.0f,
                 1.0f, 1.0f,-1.0f,
                -1.0f, 1.0f,-1.0f,
                 1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f,-1.0f,
                -1.0f, 1.0f, 1.0f,
                 1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f,
                 1.0f,-1.0f, 1.0f
        };

    // One color for each vertex. They were generated randomly.
    static const GLfloat g_color_buffer_data[] = {
                0.583f,  0.771f,  0.014f,
                0.609f,  0.115f,  0.436f,
                0.327f,  0.483f,  0.844f,
                0.822f,  0.569f,  0.201f,
                0.435f,  0.602f,  0.223f,
                0.310f,  0.747f,  0.185f,
                0.597f,  0.770f,  0.761f,
                0.559f,  0.436f,  0.730f,
                0.359f,  0.583f,  0.152f,
                0.483f,  0.596f,  0.789f,
                0.559f,  0.861f,  0.639f,
                0.195f,  0.548f,  0.859f,
                0.014f,  0.184f,  0.576f,
                0.771f,  0.328f,  0.970f,
                0.406f,  0.615f,  0.116f,
                0.676f,  0.977f,  0.133f,
                0.971f,  0.572f,  0.833f,
                0.140f,  0.616f,  0.489f,
                0.997f,  0.513f,  0.064f,
                0.945f,  0.719f,  0.592f,
                0.543f,  0.021f,  0.978f,
                0.279f,  0.317f,  0.505f,
                0.167f,  0.620f,  0.077f,
                0.347f,  0.857f,  0.137f,
                0.055f,  0.953f,  0.042f,
                0.714f,  0.505f,  0.345f,
                0.783f,  0.290f,  0.734f,
                0.722f,  0.645f,  0.174f,
                0.302f,  0.455f,  0.848f,
                0.225f,  0.587f,  0.040f,
                0.517f,  0.713f,  0.338f,
                0.053f,  0.959f,  0.120f,
                0.393f,  0.621f,  0.362f,
                0.673f,  0.211f,  0.457f,
                0.820f,  0.883f,  0.371f,
                0.982f,  0.099f,  0.879f
        };

	crap::opengl::buffer vertex_buffer( crap::opengl::array_buffer, crap::opengl::static_draw );
	vertex_buffer.bind();
	vertex_buffer.set_data( sizeof(g_vertex_buffer_data), (void*)g_vertex_buffer_data );

	crap::opengl::buffer color_buffer( crap::opengl::array_buffer, crap::opengl::static_draw );
	color_buffer.bind();
	color_buffer.set_data( sizeof(g_color_buffer_data), (void*)g_color_buffer_data );

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

        // 1rst attribute buffer : vertices
		shader.vertex_attribute_array.enable(0);
		vertex_buffer.bind();
		shader.vertex_attribute_array.pointer( 0, 3, false, 0, (void*)0);

        // 2nd attribute buffer : colors
        shader.vertex_attribute_array.enable(1);
		color_buffer.bind();
		shader.vertex_attribute_array.pointer( 1, 3, false, 0, (void*)0);

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles

		shader.vertex_attribute_array.disable(0);
		shader.vertex_attribute_array.disable(1);

		window.swap();
		window.poll_events();
		joy.poll_events();
	}
}
