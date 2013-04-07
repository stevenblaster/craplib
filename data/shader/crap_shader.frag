#version 330 core

// input
in vec2 model_uv;
in vec3 world_position;
in vec3 camera_normal;
in vec3 camera_eye_direction;
in vec3 camera_light_direction;
in vec3 tangent_eye_direction;
in vec3 tangent_light_direction;

// output
out vec3 color;

// uniforms
uniform mat4 world_matrix; //MVP
uniform mat4 view_matrix; //V
uniform mat4 model_matrix; //M;
uniform mat3 model_view_matrix; //MV3x3;
uniform sampler2D diffuse_texture;
uniform sampler2D normal_texture;
uniform sampler2D specular_texture;
uniform int specular_type;
uniform vec3 light_position; //LightPosition_worldspace;
uniform mat3 light_view_matrix;
uniform int light_type;

uniform vec3 light_color;
uniform float light_power;

uniform vec3 ambient_color;
uniform vec3 specular_color;

void main(){

	// Material properties
	vec3 material_diffuse_color = texture2D( diffuse_texture, model_uv ).rgb * light_color;
	vec3 material_ambient_color = material_diffuse_color * ambient_color;
	vec3 material_specular_color = texture2D( specular_texture, model_uv ).rgb * specular_color;

	// Local normal, in tangent space. V tex coordinate is inverted because normal map is in TGA (not in DDS) for better quality
	vec3 tangent_texture_normal = normalize(texture2D( normal_texture, vec2(model_uv.x,-model_uv.y) ).rgb*2 - 1.0);
	
	// Distance to the light
	float distance = length( light_position - world_position );

	// Normal of the computed fragment, in camera space , vec3 n = normalize( Normal_cameraspace );
	vec3 n = tangent_texture_normal;

	// Direction of the light (from the fragment to the light)
	vec3 l = normalize( camera_light_direction );

	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( n,l ), 0,1 );
	
	// Eye vector (towards the camera)
	vec3 E = normalize(camera_eye_direction);

	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);

	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( E,R ), 0,1 );
	
	color = 
		// Ambient : simulates indirect lighting
		material_ambient_color +
		// Diffuse : "color" of the object
		material_diffuse_color * light_color * light_power * cosTheta / (distance*distance) +
		// Specular : reflective highlight, like a mirror
		material_specular_color * light_color * light_power * pow(cosAlpha,5) / (distance*distance);

}