#version 330 core

// input
in vec2 model_uv;
in vec3 world_position;
in vec3 camera_eye_direction;
in vec3 tangent_eye_direction;

in vec3 camera_light_direction1;
in vec3 tangent_light_direction1;
in vec3 camera_light_direction2;
in vec3 tangent_light_direction2;
in vec3 camera_light_direction3;
in vec3 tangent_light_direction3;

// output
out vec3 color;

// uniforms
uniform mat4 world_matrix; 
uniform mat4 view_matrix;
uniform mat4 model_matrix; 
uniform mat3 model_view_matrix;

uniform sampler2D diffuse_texture;
uniform sampler2D normal_texture;

uniform int lightType1;
uniform int lightType2;
uniform int lightType3;

uniform int specType;
uniform int bumpEnabled;

struct lightSource
{
  vec4 position;
  vec4 diffuse;
  vec4 specular;
  float constantAttenuation, linearAttenuation, quadraticAttenuation;
  float spotCutoff, spotExponent;
  vec3 spotDirection;
};

//const int numberOfLights = 3; 
const int numberOfLights = 1; // ONLY ONE LIGHT ATM
lightSource lights[numberOfLights];

lightSource light0 = lightSource(
  vec4(0.0,  1.0,  2.0, 1.0),
  vec4(1.0,  1.0,  1.0, 1.0),
  vec4(1.0,  1.0,  1.0, 1.0),
  0.0, 1.0, 0.0,
  180.0, 0.0,
  vec3(0.0, 0.0, 0.0)
);

lightSource light1 = lightSource(
    vec4(0.0, -2.0,  0.0, 1.0),
    vec4(2.0,  0.0,  0.0, 1.0),
    vec4(0.1,  0.1,  0.1, 1.0),
    0.0, 1.0, 0.0,
    80.0, 10.0,
    vec3(0.0, 1.0, 0.0)
);

lightSource light2 = lightSource(
    vec4(3.0, -3.0,  0.0, 1.0),
    vec4(2.0,  0.0,  0.0, 1.0),
    vec4(0.1,  0.1,  0.1, 1.0),
    0.0, 1.0, 0.0,
    80.0, 10.0,
    vec3(0.0, 1.0, 0.0)
);


void main()
{
	lights[0] = light0;
	//lights[1] = light1;
	//lights[2] = light2;
	
	int lightTypes[numberOfLights];
	lightTypes[0] = lightType1;
	//lightTypes[1] = lightType2;
	//lightTypes[2] = lightType3;
	
	vec3 camera_light_dir[numberOfLights];
	vec3 tangent_light_dir[numberOfLights];
	
	camera_light_dir[0] = camera_light_direction1;
	//camera_light_dir[1] = camera_light_direction2;
	//camera_light_dir[2] = camera_light_direction3;
	
	tangent_light_dir[0] = tangent_light_direction1;
	//tangent_light_dir[1] = tangent_light_direction2;
	//tangent_light_dir[2] = tangent_light_direction3;
	
	vec3 colors[numberOfLights];

	for(int i = 0; i < numberOfLights; ++i)
	{
		// Material properties
		vec3 material_diffuse_color = texture2D( diffuse_texture, model_uv ).rgb;
		vec3 material_ambient_color = material_diffuse_color;
		vec3 material_specular_color = material_ambient_color;

		// Local normal, in tangent space. V tex coordinate is inverted because normal map is in TGA (not in DDS) for better quality
		vec3 tangent_texture_normal = normalize(texture2D( normal_texture, vec2(model_uv.x,-model_uv.y) ).rgb * 2.0 - 1.0);

		// Distance to the light
		float distance = length( lights[i].position.xyz - world_position );

		// Normal of the computed fragment, in camera space , vec3 n = normalize( Normal_cameraspace );
		vec3 fragment_normal = tangent_texture_normal;

		// Direction of the light (from the fragment to the light)
		vec3 light_direction;
		if( lightTypes[i] == 0 )
			light_direction = normalize( camera_light_dir[i] ); //pointlight
		else
			light_direction = normalize( lights[i].position.xyz ); //directional light - see pos as dir

		// Cosine of the angle between the normal and the light direction,
		// clamped above 0
		// - light is at the vertical of the triangle -> 1
		// - light is perpendicular to the triangle -> 0
		// - light is behind the triangle -> 0
		float cosTheta = clamp( dot( fragment_normal, light_direction ), 0,1 );

		// Eye vector (towards the camera)
		vec3 camera_direction = normalize(camera_eye_direction);
		//vec3 tangent_direction = normalize(tangent_eye_direction);

		// Direction in which the triangle reflects the light	
		vec3 reflection_direction = reflect(-light_direction, fragment_normal);

		// Cosine of the angle between the Eye vector and the Reflect vector,
		// clamped to 0
		// - Looking into the reflection -> 1
		// - Looking elsewhere -> < 1

		float cosAlpha;
		if( specType == 0 )
			cosAlpha = clamp( dot( camera_direction, reflection_direction ), 0,1 ); //BLINN
		else
			cosAlpha = pow( max(dot(reflection_direction, camera_direction), 0.0), 0.3 ); //PHONG

		colors[i] =
		// Ambient : simulates indirect lighting
		material_ambient_color +
		// Diffuse : "color" of the object
		material_diffuse_color * lights[i].diffuse.xyz * cosTheta / (distance*distance) +
		// Specular : reflective highlight, like a mirror
		material_specular_color * lights[i].specular.xyz * lights[i].spotExponent * pow(cosAlpha,5) / (distance*distance);
	}
	
	for(int i=0; i< numberOfLights; ++i)
	{
		color += colors[i];
	}
}