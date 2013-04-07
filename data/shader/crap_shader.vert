#version 330 core

// vertex data
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_uv;
layout(location = 2) in vec3 vertex_normal;
layout(location = 3) in vec3 vertex_tangent;
layout(location = 4) in vec3 vertex_binormal;

// output
out vec2 model_uv;
out vec3 world_position;
out vec3 camera_eye_direction;
out vec3 tangent_eye_direction;

out vec3 camera_light_direction[gl_MaxLights];
out vec3 tangent_light_direction[gl_MaxLights];

// uniforms
uniform mat4 world_matrix; 
uniform mat4 view_matrix;
uniform mat4 model_matrix; 
uniform mat3 model_view_matrix;

uniform sampler2D diffuse_texture;
uniform sampler2D normal_texture;

uniform int light_number = 1;
//uniform gl_LightSourceParameters gl_LightSource[gl_MaxLights];

void main()
{	
	// position of vertex in clipspace
	gl_Position =  world_matrix * vec4(vertex_position,1);
	
	// Position of the vertex, in worldspace
	world_position = (model_matrix * vec4(vertex_position,1)).xyz;
	
	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 camera_vertex_position = ( view_matrix * model_matrix * vec4(vertex_position,1)).xyz;
	camera_eye_direction = vec3(0,0,0) - camera_vertex_position;

	for( int i=0; i< light_number; ++i)
	{
		// Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
		vec3 camera_light_position = ( view_matrix * vec4( gl_LightSource[i].position )).xyz;
		camera_light_direction[i] = camera_light_position + camera_eye_direction;
	}
	
	// UV of the vertex. No special space for this one.
	model_uv = vertex_uv;

	// model to camera = ModelView
	vec3 camera_vertex_normal = model_view_matrix * vertex_normal;
	vec3 camera_vertex_tangent = model_view_matrix * vertex_tangent;
	vec3 camera_vertex_binormal = model_view_matrix * vertex_binormal;
	
	mat3 TBN = transpose(mat3(
		camera_vertex_tangent,
		camera_vertex_binormal,
		camera_vertex_normal	
	)); 
	
	//tangent_eye_direction =  TBN * camera_eye_direction;

	for( int i=0; i< light_number; ++i)
	{
		tangent_light_direction[i] = TBN * camera_light_direction[i];	
	}
}

