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
out vec3 camera_normal;
out vec3 camera_eye_direction;
out vec3 camera_light_direction1;
out vec3 camera_light_direction2;
out vec3 camera_light_direction3;
out vec3 tangent_eye_direction;
out vec3 tangent_light_direction1;
out vec3 tangent_light_direction2;
out vec3 tangent_light_direction3;

// uniforms
uniform mat4 world_matrix; //MVP
uniform mat4 view_matrix; //V
uniform mat4 model_matrix; //M;
uniform mat3 model_view_matrix; //MV3x3;
uniform sampler2D diffuse_texture;
uniform sampler2D normal_texture;
uniform sampler2D specular_texture;
uniform vec3 ambient_color;

//uniform lights
uniform int specular_type1; //0=none, 1=blinn, 2=phong
uniform vec3 light_position1; //LightPosition_worldspace;
uniform mat3 light_view_matrix1;
uniform int light_type1; //0=none, 1=point, 2=directional, 3=spot
uniform vec3 light_color1;
uniform float light_power1;
uniform vec3 specular_color1;

//uniform lights
uniform int specular_type2; //0=none, 1=blinn, 2=phong
uniform vec3 light_position2; //LightPosition_worldspace;
uniform mat3 light_view_matrix2;
uniform int light_type2; //0=none, 1=point, 2=directional, 3=spot
uniform vec3 light_color2;
uniform float light_power2;
uniform vec3 specular_color2;

//uniform lights
uniform int specular_type3; //0=none, 1=blinn, 2=phong
uniform vec3 light_position3; //LightPosition_worldspace;
uniform mat3 light_view_matrix3;
uniform int light_type3; //0=none, 1=point, 2=directional, 3=spot
uniform vec3 light_color3;
uniform float light_power3;
uniform vec3 specular_color3;

void main(){

	if( light_type1 == 1 )
	{

		// position of vertex in clipspace
		gl_Position =  world_matrix * vec4(vertex_position,1);
		
		// Position of the vertex, in worldspace
		world_position = (model_matrix * vec4(vertex_position,1)).xyz;
		
		// Vector that goes from the vertex to the camera, in camera space.
		// In camera space, the camera is at the origin (0,0,0).
		vec3 camera_vertex_position = ( view_matrix * model_matrix * vec4(vertex_position,1)).xyz;
		camera_eye_direction = vec3(0,0,0) - camera_vertex_position;

		// Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
		vec3 camera_light_position1 = ( view_matrix * vec4(light_position1,1)).xyz;
		camera_light_direction1 = camera_light_position1 + camera_eye_direction;
		
		// Normal of the the vertex, in camera space
		// Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
		camera_normal = ( view_matrix * model_matrix * vec4(vertex_normal,0)).xyz; 
		
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
		)); // You can use dot products instead of building this matrix and transposing it. See References for details.

		tangent_light_direction1 = TBN * camera_light_direction1;
		tangent_eye_direction =  TBN * camera_eye_direction;
	}
	
	if( light_type2 == 1 )
	{

		// position of vertex in clipspace
		gl_Position =  world_matrix * vec4(vertex_position,1);
		
		// Position of the vertex, in worldspace
		world_position = (model_matrix * vec4(vertex_position,1)).xyz;
		
		// Vector that goes from the vertex to the camera, in camera space.
		// In camera space, the camera is at the origin (0,0,0).
		vec3 camera_vertex_position = ( view_matrix * model_matrix * vec4(vertex_position,1)).xyz;
		camera_eye_direction = vec3(0,0,0) - camera_vertex_position;

		// Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
		vec3 camera_light_position2 = ( view_matrix * vec4(light_position2,1)).xyz;
		camera_light_direction2 = camera_light_position2 + camera_eye_direction;
		
		// Normal of the the vertex, in camera space
		// Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
		camera_normal = ( view_matrix * model_matrix * vec4(vertex_normal,0)).xyz; 
		
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
		)); // You can use dot products instead of building this matrix and transposing it. See References for details.

		tangent_light_direction2 = TBN * camera_light_direction2;
		tangent_eye_direction =  TBN * camera_eye_direction;
	}
	
	if( light_type3 == 1 )
	{

		// position of vertex in clipspace
		gl_Position =  world_matrix * vec4(vertex_position,1);
		
		// Position of the vertex, in worldspace
		world_position = (model_matrix * vec4(vertex_position,1)).xyz;
		
		// Vector that goes from the vertex to the camera, in camera space.
		// In camera space, the camera is at the origin (0,0,0).
		vec3 camera_vertex_position = ( view_matrix * model_matrix * vec4(vertex_position,1)).xyz;
		camera_eye_direction = vec3(0,0,0) - camera_vertex_position;

		// Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
		vec3 camera_light_position3 = ( view_matrix * vec4(light_position3,1)).xyz;
		camera_light_direction1 = camera_light_position3 + camera_eye_direction;
		
		// Normal of the the vertex, in camera space
		// Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
		camera_normal = ( view_matrix * model_matrix * vec4(vertex_normal,0)).xyz; 
		
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
		)); // You can use dot products instead of building this matrix and transposing it. See References for details.

		tangent_light_direction3 = TBN * camera_light_direction3;
		tangent_eye_direction =  TBN * camera_eye_direction;
	}
}

