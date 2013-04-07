#version 330 core

// should be done otherwise
#define MAX_LIGHTS 8

// info structs
struct light_info
{
	int specular_type;
	int light_type;

	vec3 light_position; 
	float light_power;

	vec3 light_color;
	vec3 ambient_color;
	vec3 specular_color;
	
	vec3 camera_light_direction;
	vec3 tangent_light_direction;
};

// input
in vec2 model_uv;
in vec3 world_position;
in vec3 camera_eye_direction;
in vec3 tangent_eye_direction;

in light_info light_data[MAX_LIGHTS];

// output
out vec3 color;

// uniforms
uniform mat4 world_matrix; 
uniform mat4 view_matrix;
uniform mat4 model_matrix; 
uniform mat3 model_view_matrix;

uniform sampler2D diffuse_texture;
uniform sampler2D normal_texture;

uniform int light_number;

void main()
{
	vec3 colors[MAX_LIGHTS];

	for(int i=0; i< light_number; ++i)
	{
		// Material properties
		vec3 material_diffuse_color = texture2D( diffuse_texture, model_uv ).rgb;
		vec3 material_ambient_color = material_diffuse_color * light_data[i].ambient_color;
		vec3 material_specular_color = material_ambient_color;

		// Local normal, in tangent space. V tex coordinate is inverted because normal map is in TGA (not in DDS) for better quality
		vec3 tangent_texture_normal = normalize(texture2D( normal_texture, vec2(model_uv.x,-model_uv.y) ).rgb * 2.0 - 1.0);
		
		// Distance to the light
		float distance = length( light_data[i].light_position - world_position );

		// Normal of the computed fragment, in camera space , vec3 n = normalize( Normal_cameraspace );
		vec3 fragment_normal = tangent_texture_normal;

		// Direction of the light (from the fragment to the light)
		vec3 light_direction;
		if( light_data[i].light_type == 0 )
			light_direction = normalize( light_data[i].camera_light_direction ); //pointlight
		else
			light_direction = normalize( light_data[i].light_position ); //directional light - see pos as dir

		// Cosine of the angle between the normal and the light direction, 
		// clamped above 0
		//  - light is at the vertical of the triangle -> 1
		//  - light is perpendicular to the triangle -> 0
		//  - light is behind the triangle -> 0
		float cosTheta = clamp( dot( fragment_normal, light_direction ), 0,1 );
		
		// Eye vector (towards the camera)
		vec3 camera_direction = normalize(camera_eye_direction);
		vec3 tangent_direction = normalize(tangent_eye_direction);

		// Direction in which the triangle reflects the light
		vec3 reflection_direction = reflect(-light_direction, fragment_normal);

		// Cosine of the angle between the Eye vector and the Reflect vector,
		// clamped to 0
		//  - Looking into the reflection -> 1
		//  - Looking elsewhere -> < 1
		
		float cosAlpha;
		if( light_data[i].specular_type == 0 )
			cosAlpha = clamp( dot( camera_direction, reflection_direction ), 0,1 ); //BLINN
		else
			cosAlpha = pow( max(dot(reflection_direction, camera_direction), 0.0), 0.3 ); //PHONG
		
		colors[i] = 
			// Ambient : simulates indirect lighting
			material_ambient_color +
			// Diffuse : "color" of the object
			material_diffuse_color * light_data[i].light_color * light_data[i].light_power * cosTheta / (distance*distance) +
			// Specular : reflective highlight, like a mirror
			material_specular_color * light_data[i].specular_color * light_data[i].light_power * pow(cosAlpha,5) / (distance*distance);
	}
	
	for(int i=0; i< light_number; ++i)
	{
		color += colors[i];
	}
}