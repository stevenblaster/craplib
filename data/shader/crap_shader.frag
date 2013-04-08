#version 330 core

// should be done otherwise
#define MAX_LIGHTS 3

// input
in vec2 model_uv;
in vec3 world_position;
in vec3 camera_eye_direction;
in vec3 tangent_eye_direction;

//in light_info light_data[MAX_LIGHTS];
in flat int specular_type[MAX_LIGHTS];
in flat int light_type[MAX_LIGHTS];
in vec3 light_position[MAX_LIGHTS];
in float light_power[MAX_LIGHTS];
in vec3 specular_color[MAX_LIGHTS];
in vec3 camera_light_direction[MAX_LIGHTS];
in vec3 tangent_light_direction[MAX_LIGHTS];
in vec3 vert_normal;

// output
out vec3 color;

// uniforms
uniform mat4 world_matrix; 
uniform mat4 view_matrix;
uniform mat4 model_matrix; 
uniform mat3 model_view_matrix;
uniform int bump[MAX_LIGHTS];
uniform sampler2D diffuse_texture;
uniform sampler2D normal_texture;

uniform int light_number = 1;

void main()
{
	vec3 colors[MAX_LIGHTS];
	
	// Material properties
		vec3 material_diffuse_color = texture2D( diffuse_texture, model_uv ).rgb;
		vec3 material_ambient_color = material_diffuse_color * vec3(0.1, 0.1, 0.1);
		vec3 material_specular_color = material_ambient_color;

	for(int i=0; i< light_number; ++i)
	{
		// Local normal
		vec3 tangent_texture_normal;
		if( bump[i] == 1 )
			tangent_texture_normal = normalize(texture2D( normal_texture, vec2(model_uv.x,-model_uv.y) ).rgb * 2.0 - 1.0);
		else
			tangent_texture_normal = vert_normal;
		
		// Distance to the light
		float distance = length( light_position[i] - world_position );

		// Normal of the computed fragment, in camera space , vec3 n = normalize( Normal_cameraspace );
		vec3 fragment_normal = tangent_texture_normal;

		// Direction of the light (from the fragment to the light)
		vec3 light_direction;
		if( light_type[i] == 0 )
			light_direction = normalize( camera_light_direction[i] ); //pointlight
		else
			light_direction = normalize( light_position[i] ); //directional light - see pos as dir

		// Cosine of the angle between the normal and the light direction, 
		// clamped above 0
		//  - light is at the vertical of the triangle -> 1
		//  - light is perpendicular to the triangle -> 0
		//  - light is behind the triangle -> 0
		float cosTheta;
		
		
		// Eye vector (towards the camera)
		vec3 camera_direction = normalize(camera_eye_direction);
		//vec3 tangent_direction = normalize(tangent_eye_direction);

		// Direction in which the triangle reflects the light
		vec3 reflection_direction = reflect(-light_direction, fragment_normal);
		
		vec3 half_vec = normalize(reflection_direction + light_direction);
		
		
		if( specular_type[i] == 1 )
			cosTheta = clamp( dot( fragment_normal, light_direction ), 0,1 );
		else
			cosTheta = clamp( dot( fragment_normal, half_vec ), 0,1 );

		// Cosine of the angle between the Eye vector and the Reflect vector,
		// clamped to 0
		//  - Looking into the reflection -> 1
		//  - Looking elsewhere -> < 1
		
		float cosAlpha;
		//if( specular_type[i] == 0 )
			cosAlpha = clamp( dot( camera_direction, reflection_direction ), 0,1 ); //PHONG
		//else
			//cosAlpha = pow( max(dot(reflection_direction, camera_direction), 0.0), 0.3 ); //PHONG
		
		colors[i] = 
			// Ambient : simulates indirect lighting
			material_ambient_color +
			// Diffuse : "color" of the object
			material_diffuse_color * light_power[i] * cosTheta / (distance*distance) +
			// Specular : reflective highlight, like a mirror
			material_specular_color * specular_color[i] * light_power[i] * pow(cosAlpha,5) / (distance*distance);
	}
	
	for(int i=0; i< light_number; ++i)
	{
		color += colors[i];
	}
}