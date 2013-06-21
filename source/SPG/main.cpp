#include "precompiled.h"

#include "GL/glew.h"

#if defined( CRAP_PLATFORM_WIN )
#include <gl/GL.h>
#include <gl/GLU.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif


#include "opengl/renderwindow.h"
#include "opengl/setup.h"
#include "opengl/keyboard.h"
#include "opengl/mouse.h"
#include "opengl/buffer.h"

#include "math/vector3.h"
#include "math/vector2.h"

#include "files/file.h"
#include "audio/audiodevice.h"
#include "files/wavefile.h"

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

#include "objloader.hpp"
#include "vboindexer.hpp"
#include "tangentspace.hpp"

//for antweakshit
#define GLFW_CDECL
#define MAX_LIGHTS 3

// Include AntTweakBar
#include <AntTweakBar.h>

void handleInput(crap::keyboard& keyboard, crap::mouse& mouse, camera& cam);
crap::vector2i mouse_pos;

void gui_mouse_down( i32 key )
{
	TwEventMouseButtonGLFW( key, 1 );
}

void gui_mouse_up( i32 key )
{
	TwEventMouseButtonGLFW( key, 0 );
}

int main( void )
{

	crap::audiodevice audio_device;
	
	/*
	openalcode



	*/

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

	//camera setup
	camera cam;
	cam.setPosition( glm::vec3( 0.0f, 0.0f, 5.0f ) );
	mouse_pos = mouse.position();

	//create contentmanager
	content_manager cm;
	cm.init( "spg.ini" );

	//create vertex array
	crap::vertex_array vert_array;
	vert_array.bind();

	//test: load vbo onto GPU
	vbo cube_vbo( "cube", &cm, vbo::static_draw );
	vbo ape_vbo("ape", &cm, vbo::static_draw );
	vbo cube_big_vbo( "cube", &cm, vbo::static_draw );
	//vbo people_vbo("people", &cm, vbo::static_draw );

	//////////////////////////
	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loadOBJ("../../../data/geometry/dupercube.obj", vertices, uvs, normals);

	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;
	computeTangentBasis(
		vertices, uvs, normals, // input
		tangents, bitangents    // output
	);

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	std::vector<glm::vec3> indexed_tangents;
	std::vector<glm::vec3> indexed_bitangents;
	indexVBO_TBN(
		vertices, uvs, normals, tangents, bitangents, 
		indices, indexed_vertices, indexed_uvs, indexed_normals, indexed_tangents, indexed_bitangents
	);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	GLuint tangentbuffer;
	glGenBuffers(1, &tangentbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_tangents.size() * sizeof(glm::vec3), &indexed_tangents[0], GL_STATIC_DRAW);

	GLuint bitangentbuffer;
	glGenBuffers(1, &bitangentbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_bitangents.size() * sizeof(glm::vec3), &indexed_bitangents[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
	/////////////////////////

	geometry_content ig;
	cm.create_content( "cube" , &ig, type_name::geometry );

	//test: load texture onto GPU
	tbo diffuse_tbo( "stone_diff", &cm, tbo::tga );
	tbo normal_tbo( "stone_norm", &cm, tbo::tga );
	tbo height_tbo( "stone_height", &cm, tbo::tga );

	//shadow stuff
	crap::frame_buffer frame_buffer;
	frame_buffer.bind();
	tbo depthmap( "", &cm, tbo::depth );
	frame_buffer.unbind();

	//shadow stuff
	crap::quad_buffer quad_buffer;

	//test: load linked shader progam onto GPU
	shader_manager sm(&cm);
	sm.add("epr_vert", "epr_frag");
	sm.add("shadow_vert", "shadow_frag");
	
	//get stuff from shader program
	//shadow shader
	sm.set_current("shadow_vert", "shadow_frag");
	crap::uniform DepthBiasMVPID = sm.current()->uniform_location("depthMVP");

	//vertex shader
	sm.set_current("epr_vert", "epr_frag");
	crap::uniform WorldMatrixID = sm.current()->uniform_location("world_matrix4x4");
	crap::uniform ViewMatrixID = sm.current()->uniform_location("view_matrix4x4");
	crap::uniform ModelMatrixID = sm.current()->uniform_location("model_matrix4x4");
	crap::uniform ModelView3x3MatrixID = sm.current()->uniform_location("model_view_matrix3x3");

	//fragment shader
	crap::uniform DiffuseTextureID  = sm.current()->uniform_location("diffuse_texture");
	crap::uniform NormalTextureID  = sm.current()->uniform_location("normal_texture");
	crap::uniform HeightTextureID = sm.current()->uniform_location("height_texture");

	crap::uniform LightAmbientPowerID = sm.current()->uniform_location("ambient_power");

	crap::uniform LightPowerArrayID = sm.current()->uniform_location("light_power");
	crap::uniform LightSpecularTypeArrayID = sm.current()->uniform_location("light_specular_type");
	crap::uniform LightSpecularLobeArrayID = sm.current()->uniform_location("light_specular_lobe");
	crap::uniform LightColorArrayID = sm.current()->uniform_location("light_color");
	crap::uniform LightSelfShadowingOnID = sm.current()->uniform_location("selfshadowing_on");

	crap::uniform DisplacementOnID = sm.current()->uniform_location("displacement_on");
	crap::uniform DisplacementStepsID = sm.current()->uniform_location("displacement_steps");
	crap::uniform DisplacementRefinementStepsID = sm.current()->uniform_location("displacement_refinement_steps");
	crap::uniform DisplacementUVFactorID = sm.current()->uniform_location("displacement_uv_factor");

	//both shaders
	crap::uniform LightPositionArrayID = sm.current()->uniform_location("light_position");
	crap::uniform LightDirectionArrayID = sm.current()->uniform_location("light_direction");
	crap::uniform LightTypeArrayID = sm.current()->uniform_location("light_type");
	crap::uniform LightStateArrayID = sm.current()->uniform_location("light_state");

	crap::uniform LightNormalMappingOnID = sm.current()->uniform_location("normal_mapping_on");

	//shadow stuff
	crap::uniform ShadowMapID = sm.current()->uniform_location("shadow_map");
	crap::uniform ShadowMappingOnID = sm.current()->uniform_location("shadow_mapping_on");
	crap::uniform ShadowDepthBiasMVPID = sm.current()->uniform_location("depth_bias_mvp");

	//SHADER DATA
	// Projection matrix : 60° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	float display_field_of_view = 60.f; //60°
	float display_ratio_horizontal = 4.f;
	float display_ratio_vertical = 3.f;
	float display_range_near = 0.1f;
	float display_range_far = 100.f;

	glm::mat4 projection_matrix = glm::perspective(
		display_field_of_view, 
		display_ratio_horizontal / display_ratio_vertical, 
		display_range_near, 
		display_range_far);

	glm::mat4 model_matrix(1.0f);
	glm::mat4 model_view_matrix(1.0f);
	glm::mat4 view_matrix = cam.view();
	glm::mat4 world_matrix(1.0f);
	glm::mat3 model_view_matrix3x3(1.0f);

	//light stuff
	float light_ambient_power = 0.5f;
	float light_power_array[MAX_LIGHTS] = { 1.f, 1.f, 1.f };
	int light_specular_type_array[MAX_LIGHTS] = { 1, 1, 1 };
	float light_specular_lobe_array[MAX_LIGHTS] = { 100.f, 100.f, 100.f };
	glm::vec3 light_color_array[MAX_LIGHTS] = { glm::vec3(1.f), glm::vec3(1.f), glm::vec3(1.f) };
	int light_self_shadowing_on = 1;
	glm::vec3 light_position_array[MAX_LIGHTS] = { glm::vec3(4,0,0), glm::vec3(0,0,-4), glm::vec3(4,4,4) };
	glm::vec3 light_direction_array[MAX_LIGHTS] = { glm::vec3(-4,0,0), glm::vec3(0,0,4), glm::vec3(-4,-4,-4) };
	int light_type_array[MAX_LIGHTS] = { 0, 0, 0 };
	int light_state_array[MAX_LIGHTS] = { 1, 0, 0 };
	int light_normal_mapping_on = 1;

	//shadowstuff
	int shadow_mapping_on = 1;

	//displacement stuff
	int displacement_on = 1;
	float displacement_steps = 20;
	float displacement_refinement_steps = 20;
	float displacmenet_uv_factor = 20;

	//GUI
	TwInit(TW_OPENGL, NULL);
	TwWindowSize(1024, 768);

	TwBar * GeneralGUI = TwNewBar("General settings");
	TwBar * LightGUI = TwNewBar("Light Settings");
	TwBar * DisplacementGUI = TwNewBar("Displacement Settings");

	TwSetParam(GeneralGUI, NULL, "refresh", TW_PARAM_CSTRING, 1, "0.1");
	TwSetParam(LightGUI, NULL, "refresh", TW_PARAM_CSTRING, 1, "0.1");
	TwSetParam(DisplacementGUI, NULL, "refresh", TW_PARAM_CSTRING, 1, "0.1");

	//general gui
	TwAddSeparator(GeneralGUI, "Funny seperator", NULL);
	TwAddVarRW(GeneralGUI, "Field of View", TW_TYPE_FLOAT , &display_field_of_view, "help='Field of View value'");
	TwAddVarRW(GeneralGUI, "Ratio Horizontal", TW_TYPE_FLOAT , &display_ratio_horizontal, "help='Ratio Horizontal'");
	TwAddVarRW(GeneralGUI, "Ratio Vertical", TW_TYPE_FLOAT , &display_ratio_vertical, "help='Ratio Vertical'");
	TwAddVarRW(GeneralGUI, "Range Near", TW_TYPE_FLOAT , &display_range_near, "help='Range near'");
	TwAddVarRW(GeneralGUI, "Range far", TW_TYPE_FLOAT , &display_range_far, "help='Range far'");

	//light gui
	TwAddVarRW(LightGUI, "Ambient light", TW_TYPE_FLOAT , &light_ambient_power, "help='Ambient power'");
	TwAddVarRW(LightGUI, "Self Shadowing", TW_TYPE_BOOL32, &light_self_shadowing_on, NULL);
	TwAddVarRW(LightGUI, "Normal Mapping", TW_TYPE_BOOL32, &light_normal_mapping_on, NULL);
	TwType gui_light_type = TwDefineEnumFromString("LightType", "Directionallight,Pointlight");
	TwType gui_light_specular_type = TwDefineEnumFromString("LightSpecularType", "Blinn,Phong");
	//shadow
	TwAddVarRW(LightGUI, "Cast Shadows", TW_TYPE_BOOL32, &shadow_mapping_on, NULL);
	//light1
	TwAddVarRW(LightGUI, "Light 1", TW_TYPE_BOOL32, light_state_array, NULL);
	TwAddVarRW(LightGUI, "Light Type 1", gui_light_type, light_type_array, NULL);
	TwAddVarRW(LightGUI, "Light Specular Type 1", gui_light_specular_type, light_specular_type_array, NULL);
	TwAddVarRW(LightGUI, "Light Power 1", TW_TYPE_FLOAT , light_power_array, NULL);
	TwAddVarRW(LightGUI, "Light Specular Lobe 1", TW_TYPE_FLOAT , light_specular_lobe_array, NULL);
	TwAddVarRW(LightGUI, "Light Color 1", TW_TYPE_COLOR3F , light_color_array, NULL);
	TwAddVarRW(LightGUI, "Light Position 1", TW_TYPE_DIR3F , light_position_array, NULL);
	TwAddVarRW(LightGUI, "Light Direction 1", TW_TYPE_DIR3F , light_direction_array, NULL);
	//light2
	TwAddVarRW(LightGUI, "Light 2", TW_TYPE_BOOL32, light_state_array+1, NULL);
	TwAddVarRW(LightGUI, "Light Type 2", gui_light_type, light_type_array+1, NULL);
	TwAddVarRW(LightGUI, "Light Specular Type 2", gui_light_specular_type, light_specular_type_array+1, NULL);
	TwAddVarRW(LightGUI, "Light Power 2", TW_TYPE_FLOAT , light_power_array+1, NULL);
	TwAddVarRW(LightGUI, "Light Specular Lobe 2", TW_TYPE_FLOAT , light_specular_lobe_array+1, NULL);
	TwAddVarRW(LightGUI, "Light Color 2", TW_TYPE_COLOR3F , light_color_array+1, NULL);
	TwAddVarRW(LightGUI, "Light Position 2", TW_TYPE_DIR3F , light_position_array+1, NULL);
	TwAddVarRW(LightGUI, "Light Direction 2", TW_TYPE_DIR3F , light_direction_array+1, NULL);
	//light3
	TwAddVarRW(LightGUI, "Light 3", TW_TYPE_BOOL32, light_state_array+2, NULL);
	TwAddVarRW(LightGUI, "Light Type 3", gui_light_type, light_type_array+2, NULL);
	TwAddVarRW(LightGUI, "Light Specular Type 3", gui_light_specular_type, light_specular_type_array+2, NULL);
	TwAddVarRW(LightGUI, "Light Power 3", TW_TYPE_FLOAT , light_power_array+2, NULL);
	TwAddVarRW(LightGUI, "Light Specular Lobe 3", TW_TYPE_FLOAT , light_specular_lobe_array+2, NULL);
	TwAddVarRW(LightGUI, "Light Color 3", TW_TYPE_COLOR3F , light_color_array+2, NULL);
	TwAddVarRW(LightGUI, "Light Position 3", TW_TYPE_DIR3F , light_position_array+2, NULL);
	TwAddVarRW(LightGUI, "Light Direction 3", TW_TYPE_DIR3F , light_direction_array+2, NULL);

	//displacement gui
	TwAddVarRW(DisplacementGUI, "Displacement ON/OFF", TW_TYPE_BOOL32, &displacement_on, NULL);
	TwAddVarRW(DisplacementGUI, "Displacment steps", TW_TYPE_FLOAT , &displacement_steps, NULL);
	TwAddVarRW(DisplacementGUI, "Displacement refinement", TW_TYPE_FLOAT , &displacement_refinement_steps, NULL);
	TwAddVarRW(DisplacementGUI, "Displacement UV factor", TW_TYPE_FLOAT , &displacmenet_uv_factor, NULL);

	//gui mouse setup
	mouse.set_on_pressed_function( (crap::mouse::user_button_callback_function)gui_mouse_down );
	mouse.set_on_release_function( (crap::mouse::user_button_callback_function)gui_mouse_up );
	mouse.set_on_move_function( (crap::mouse::user_move_callback_function)TwEventMousePosGLFW );
	mouse.set_on_wheel_function( (crap::mouse::user_wheel_callback_function)TwEventMouseWheelGLFW );
	keyboard.set_on_pressed_function( (crap::keyboard::user_callback_function)TwEventKeyGLFW );
	//todo set char input

	// temporary
	crap::opengl::clearColor(1.0f, 1.0f, 1.0f, 0.0f);

	while( !keyboard.is_pressed( crap::keyboard::key_escape ) && window.is_open() )
	{
		// update positions
		handleInput(keyboard, mouse, cam);

		crap::opengl::clear(crap::opengl::color_depth_buffer);

		frame_buffer.bind();
		glViewport(0,0,1024,1024); // Render on the whole framebuffer, complete from the lower left corner to the upper right
		sm.set_current("shadow_vert", "shadow_frag");
		sm.activate();

		glm::vec3 lightInvDir = light_direction_array[0]; //glm::vec3(0.5f,2,2);

		// Compute the MVP matrix from the light's point of view
		glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
		glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));
		glm::mat4 depthModelMatrix = glm::mat4(1.0);
		glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

		sm.current()->uniform_matrix4f_value( DepthBiasMVPID, 1, &depthMVP[0][0]);

		sm.current()->vertex_attribute_array.enable(0);
		cube_vbo.bind_buffer( vbo::verticies );
		sm.current()->vertex_attribute_array.pointer( 0, 3, crap::gl_float, false, 0, (void*)0);

		cube_vbo.bind_buffer( vbo::indicies );
		crap::opengl::draw_elements(
			crap::opengl::triangles,		// mode
			cube_vbo.indicies_size,			// count
			crap::opengl::unsigned_short	// type
		);

		sm.current()->vertex_attribute_array.disable(0);

		frame_buffer.unbind();

		glViewport(0,0,1024,768); // Render on the whole framebuffer, complete from the lower left corner to the upper right

		crap::opengl::clear(crap::opengl::color_depth_buffer);

		sm.set_current("epr_vert", "epr_frag");
		sm.activate();

		///////////////////////////////////////
		//////////////////////////////////////

		projection_matrix = glm::perspective(
			display_field_of_view, 
			display_ratio_horizontal / display_ratio_vertical, 
			display_range_near, 
			display_range_far);

		view_matrix = cam.view();
		model_view_matrix = view_matrix * world_matrix;
		model_view_matrix3x3 = glm::mat3(model_view_matrix);
		world_matrix = projection_matrix * view_matrix * model_matrix;

		glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0, 
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
		);

		glm::mat4 depthBiasMVP = biasMatrix*depthMVP;
		
		sm.current()->uniform_matrix4f_value( ShadowDepthBiasMVPID, 1, &depthBiasMVP[0][0]);
		sm.current()->uniform_1i(ShadowMappingOnID, shadow_mapping_on);

		//activate shader porgram and connect data
		//sm.activate();
		//default stuff
		sm.current()->uniform_matrix4f_value( WorldMatrixID, 1, &world_matrix[0][0]);
		sm.current()->uniform_matrix4f_value( ModelMatrixID, 1, &model_matrix[0][0]);
		sm.current()->uniform_matrix4f_value( ViewMatrixID, 1, &view_matrix[0][0]);
		sm.current()->uniform_matrix3f_value( ModelView3x3MatrixID, 1, &model_view_matrix3x3[0][0]);
		//light
		sm.activate();
		sm.current()->uniform_1f(LightAmbientPowerID, light_ambient_power);
		sm.current()->uniform_1i(LightSelfShadowingOnID, light_self_shadowing_on);
		sm.current()->uniform_1i(LightNormalMappingOnID, light_normal_mapping_on);
		sm.current()->uniform_1f_value( LightPowerArrayID, 3, light_power_array );
		sm.current()->uniform_1i_value( LightSpecularTypeArrayID, 3, light_specular_type_array );
		sm.current()->uniform_1f_value( LightSpecularLobeArrayID, 3, light_specular_lobe_array );
		sm.current()->uniform_3f_value( LightColorArrayID, 3, (f32*)light_color_array );
		sm.current()->uniform_3f_value( LightPositionArrayID, 3, (f32*)light_position_array );
		sm.current()->uniform_3f_value( LightDirectionArrayID, 3, (f32*)light_direction_array );
		sm.current()->uniform_1i_value( LightTypeArrayID, 3, light_type_array );
		sm.current()->uniform_1i_value( LightStateArrayID, 3, light_state_array );
		//displacement
		sm.current()->uniform_1i( DisplacementOnID, displacement_on );
		sm.current()->uniform_1f( DisplacementStepsID, displacement_steps);
		sm.current()->uniform_1f( DisplacementRefinementStepsID, displacement_refinement_steps);
		sm.current()->uniform_1f( DisplacementUVFactorID, displacmenet_uv_factor);

		//activate texture buffer and connect data
		diffuse_tbo.activate();
		diffuse_tbo.bind_buffer();
		sm.current()->uniform_1i( DiffuseTextureID, 0);

		normal_tbo.activate();
		normal_tbo.bind_buffer();
		sm.current()->uniform_1i( NormalTextureID, 1);

		height_tbo.activate();
		height_tbo.bind_buffer();
		sm.current()->uniform_1i( HeightTextureID, 2 );

		depthmap.activate();
		depthmap.bind_buffer();
		sm.current()->uniform_1i( ShadowMapID, 4);

		//define data of buffers
		sm.current()->vertex_attribute_array.enable(0);
		//cube_vbo.bind_buffer( vbo::verticies );
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		sm.current()->vertex_attribute_array.pointer( 0, 3, crap::gl_float, false, 0, (void*)0);

		sm.current()->vertex_attribute_array.enable(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		//cube_vbo.bind_buffer( vbo::uvs );
		sm.current()->vertex_attribute_array.pointer( 1, 2, crap::gl_float, false, 0, (void*)0);

		sm.current()->vertex_attribute_array.enable(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		//cube_vbo.bind_buffer( vbo::normals );
		sm.current()->vertex_attribute_array.pointer( 2, 3, crap::gl_float, false, 0, (void*)0);

		sm.current()->vertex_attribute_array.enable(3);
		glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
		//cube_vbo.bind_buffer( vbo::tangents );
		sm.current()->vertex_attribute_array.pointer( 3, 3, crap::gl_float, false, 0, (void*)0);

		sm.current()->vertex_attribute_array.enable(4);
		glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
		//cube_vbo.bind_buffer( vbo::binormals );
		sm.current()->vertex_attribute_array.pointer( 4, 3, crap::gl_float, false, 0, (void*)0);

		////draw the fuck
		cube_vbo.bind_buffer( vbo::indicies );
		crap::opengl::draw_elements(
			crap::opengl::triangles,		// mode
			cube_vbo.indicies_size,			// count
			crap::opengl::unsigned_short	// type
		);

		sm.current()->vertex_attribute_array.disable(0);
		sm.current()->vertex_attribute_array.disable(1);
		sm.current()->vertex_attribute_array.disable(2);
		sm.current()->vertex_attribute_array.disable(3);
		sm.current()->vertex_attribute_array.disable(4);

		//next object
		glm::mat4 model_matrix_2 = model_matrix * glm::translate(3.f,0.f,0.f);
		model_view_matrix = view_matrix * model_matrix_2;
		model_view_matrix3x3 = glm::mat3(model_view_matrix);
		world_matrix = projection_matrix * view_matrix * model_matrix_2;

		//activate shader porgram and connect data
		//sm.activate();
		sm.current()->uniform_matrix4f_value( WorldMatrixID, 1, &world_matrix[0][0]);
		sm.current()->uniform_matrix4f_value( ModelMatrixID, 1, &model_matrix_2[0][0]);
		sm.current()->uniform_matrix3f_value( ModelView3x3MatrixID, 1, &model_view_matrix3x3[0][0]);

		//attempt
		//define data of buffers
		sm.current()->vertex_attribute_array.enable(0);
		ape_vbo.bind_buffer( vbo::verticies );
		sm.current()->vertex_attribute_array.pointer( 0, 3, crap::gl_float, false, 0, (void*)0);

		sm.current()->vertex_attribute_array.enable(1);
		ape_vbo.bind_buffer( vbo::uvs );
		sm.current()->vertex_attribute_array.pointer( 1, 2, crap::gl_float, false, 0, (void*)0);

		sm.current()->vertex_attribute_array.enable(2);
		ape_vbo.bind_buffer( vbo::normals );
		sm.current()->vertex_attribute_array.pointer( 2, 3, crap::gl_float, false, 0, (void*)0);

		sm.current()->vertex_attribute_array.enable(3);
		ape_vbo.bind_buffer( vbo::tangents );
		sm.current()->vertex_attribute_array.pointer(3, 3, crap::gl_float, false, 0, (void*)0);

		sm.current()->vertex_attribute_array.enable(4);
		ape_vbo.bind_buffer( vbo::binormals );
		sm.current()->vertex_attribute_array.pointer( 4, 3, crap::gl_float, false, 0, (void*)0);


		//draw the fuck
		ape_vbo.bind_buffer( vbo::indicies );
		crap::opengl::draw_elements(
			crap::opengl::triangles,		// mode
			ape_vbo.indicies_size,			// count
			crap::opengl::unsigned_short	// type
		);

		//disable data define stuff
		sm.current()->vertex_attribute_array.disable(0);
		sm.current()->vertex_attribute_array.disable(1);
		sm.current()->vertex_attribute_array.disable(2);
		sm.current()->vertex_attribute_array.disable(3);
		sm.current()->vertex_attribute_array.disable(4);

		//next object
		glm::mat4 model_matrix_3 = model_matrix * glm::translate(0.f,-2.f,0.f);
		model_view_matrix = view_matrix * model_matrix_2;
		model_view_matrix3x3 = glm::mat3(model_view_matrix);
		world_matrix = projection_matrix * view_matrix * model_matrix_3;

		//activate shader porgram and connect data
		//sm.activate();
		sm.current()->uniform_matrix4f_value( WorldMatrixID, 1, &world_matrix[0][0]);
		sm.current()->uniform_matrix4f_value( ModelMatrixID, 1, &model_matrix_3[0][0]);
		sm.current()->uniform_matrix3f_value( ModelView3x3MatrixID, 1, &model_view_matrix3x3[0][0]);

		//attempt
		//define data of buffers
		sm.current()->vertex_attribute_array.enable(0);
		cube_big_vbo.bind_buffer( vbo::verticies );
		sm.current()->vertex_attribute_array.pointer( 0, 3, crap::gl_float, false, 0, (void*)0);

		sm.current()->vertex_attribute_array.enable(1);
		cube_big_vbo.bind_buffer( vbo::uvs );
		sm.current()->vertex_attribute_array.pointer( 1, 2, crap::gl_float, false, 0, (void*)0);

		sm.current()->vertex_attribute_array.enable(2);
		cube_big_vbo.bind_buffer( vbo::normals );
		sm.current()->vertex_attribute_array.pointer( 2, 3, crap::gl_float, false, 0, (void*)0);

		sm.current()->vertex_attribute_array.enable(3);
		cube_big_vbo.bind_buffer( vbo::tangents );
		sm.current()->vertex_attribute_array.pointer(3, 3, crap::gl_float, false, 0, (void*)0);

		sm.current()->vertex_attribute_array.enable(4);
		cube_big_vbo.bind_buffer( vbo::binormals );
		sm.current()->vertex_attribute_array.pointer( 4, 3, crap::gl_float, false, 0, (void*)0);


		//draw the fuck
		cube_big_vbo.bind_buffer( vbo::indicies );
		crap::opengl::draw_elements(
			crap::opengl::triangles,		// mode
			cube_big_vbo.indicies_size,			// count
			crap::opengl::unsigned_short	// type
		);

		//disable data define stuff
		sm.current()->vertex_attribute_array.disable(0);
		sm.current()->vertex_attribute_array.disable(1);
		sm.current()->vertex_attribute_array.disable(2);
		sm.current()->vertex_attribute_array.disable(3);
		sm.current()->vertex_attribute_array.disable(4);

		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf((const GLfloat*)&projection_matrix[0]);
		glMatrixMode(GL_MODELVIEW);
		glm::mat4 MV = view_matrix * model_matrix;
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
			debug_light = light_position_array[0];
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
				debug_light = light_position_array[1];
				glVertex3fv(&debug_light.x);
				debug_light+=glm::vec3(1,0,0)*0.1f;
				glVertex3fv(&debug_light.x);
				debug_light-=glm::vec3(1,0,0)*0.1f;
				glVertex3fv(&debug_light.x);
				debug_light+=glm::vec3(0,1,0)*0.1f;
				glVertex3fv(&debug_light.x);
			glEnd();
	


			// light pos3
			glColor3f(1,1,1);
			glBegin(GL_LINES);
				debug_light = light_position_array[2];
				glVertex3fv(&debug_light.x);
				debug_light+=glm::vec3(1,0,0)*0.1f;
				glVertex3fv(&debug_light.x);
				debug_light-=glm::vec3(1,0,0)*0.1f;
				glVertex3fv(&debug_light.x);
				debug_light+=glm::vec3(0,1,0)*0.1f;
				glVertex3fv(&debug_light.x);
			glEnd();
		

		// Draw GUI
		TwDraw();

		//poll and swap
		window.swap();
		window.poll_events();

	}

	TwTerminate();

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
	 if( keyboard.is_pressed(crap::keyboard::key_D) || keyboard.is_pressed(crap::keyboard::key_d))
	  cam.offsetPosition( cam.right() * 0.1f);
	 if( keyboard.is_pressed(crap::keyboard::key_up) || keyboard.is_pressed(crap::keyboard::key_page_up))
	  cam.offsetPosition( cam.up() * 0.1f);
	 if( keyboard.is_pressed(crap::keyboard::key_down) || keyboard.is_pressed(crap::keyboard::key_page_down))
	  cam.offsetPosition( -cam.up() * 0.1f);

	 crap::vector2i mouse_position = mouse.position();
	 crap::vector2i screensize( 1024, 768 );
	 crap::vector2i screencenter = screensize / 2;

	 crap::vector2i move = mouse.movement();
 
	 if( mouse.is_pressed( crap::mouse::button_1 ) )
		cam.offsetOrientation( move.y / 10.0f, move.x / 10.0f );

	 //mouse.set_position( screencenter );
	 //mouse.movement();

}