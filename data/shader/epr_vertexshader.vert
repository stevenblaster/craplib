#version 330 core

// should be done otherwise
#define MAX_LIGHTS 3

// vertex data
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_uv;
layout(location = 2) in vec3 vertex_normal;
layout(location = 3) in vec3 vertex_tangent;
layout(location = 4) in vec3 vertex_binormal;

// output
out vec2 modelspace_uv;
out vec3 worldspace_position;
out vec3 cameraspace_eye_direction;
out vec3 cameraspace_light_direction[MAX_LIGHTS];
out vec3 cameraspace_normal;
out vec3 tangentspace_eye_direction;
out vec3 tangentspace_light_direction[MAX_LIGHTS];
out vec4 shadow_coordinates;

//uniforms
uniform mat4 world_matrix4x4; 
uniform mat4 view_matrix4x4;
uniform mat4 model_matrix4x4; 
uniform mat3 model_view_matrix3x3;

uniform vec3 light_position[MAX_LIGHTS];
uniform vec3 light_direction[MAX_LIGHTS];
uniform int light_type[MAX_LIGHTS];
uniform int light_state[MAX_LIGHTS];

uniform mat4 depth_bias_mvp;
uniform int shadow_mapping_on;

uniform int normal_mapping_on;


void main( void )
{
	//put into 4x4 matrix
	vec4 modelspace_position_4 = vec4(vertex_position, 1);

	// Output position of the vertex, in clip space : world_matrix4x4 * position
	gl_Position =  world_matrix4x4 * modelspace_position_4;
	
	//shadow shas
	shadow_coordinates = depth_bias_mvp * modelspace_position_4;
	
	// Position of the vertex, in worldspace : model_matrix4x4 * position
	worldspace_position = ( model_matrix4x4 * modelspace_position_4 ).xyz;
	
	// Vector that goes from the vertex to the camera, in camera space.
	vec3 cameraspace_position = (view_matrix4x4 * vec4(worldspace_position, 1)).xyz;
	cameraspace_eye_direction = vec3(0, 0, 0) - cameraspace_position;
	
	// Vector that goes from the vertex to the light, in camera space.
	for( int i = 0; i< MAX_LIGHTS; ++i )
	{
		cameraspace_light_direction[i] = vec3(0, 0, 0); //set to zero
		if( light_state[i] == 1 ) // is turned on
		{
			if( light_type[i] == 0 ) //directional light
			{
				cameraspace_light_direction[i] = (view_matrix4x4 * vec4(-light_direction[i], 0)).xyz;
			}
			else if( light_type[i] == 1 ) //point light
			{
				vec3 cameraspace_light_position = (view_matrix4x4 * vec4(light_position[i], 1)).xyz;
				cameraspace_light_direction[i] = cameraspace_light_position - cameraspace_position;
			}
		}
	}
	
	// Normal of the the vertex, in camera space
	cameraspace_normal = ( view_matrix4x4 * model_matrix4x4 * vec4(vertex_normal, 0)).xyz;
	
	// UV of the vertex. No special space for this one.
	modelspace_uv = vertex_uv;
	
	//if( normal_mapping_on == 1 )
	//{
		// model to camera = ModelView
		vec3 cameraspace_tangent = model_view_matrix3x3 * vertex_tangent;
		vec3 cameraspace_binormal = model_view_matrix3x3 * vertex_binormal;
		vec3 cameraspace_normal = model_view_matrix3x3 * vertex_normal;
		
		mat3 TBN = transpose(mat3
		(
			cameraspace_tangent,
			cameraspace_binormal,
			cameraspace_normal	
		));
		
		
		tangentspace_eye_direction =  TBN * cameraspace_eye_direction;
		
		for( int j = 0; j< MAX_LIGHTS; ++j )
		{
			tangentspace_light_direction[j] = vec3(0, 0, 0); //set to zero
			if( light_state[j] == 1 ) // is turned on
			{
				tangentspace_light_direction[j] = TBN * cameraspace_light_direction[j];
			}
		}
	//}
}