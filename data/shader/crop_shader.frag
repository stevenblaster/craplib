#version 330 core

// input
in vec2 model_uv;
in vec3 world_position;
in vec3 camera_normal;
in vec3 camera_eye_direction;
in vec3 camera_light_direction1;
in vec3 camera_light_direction2;
in vec3 camera_light_direction3;
in vec3 tangent_eye_direction;
in vec3 tangent_light_direction1;
in vec3 tangent_light_direction2;
in vec3 tangent_light_direction3;

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

	vec3 material_diffuse_color = texture2D( diffuse_texture, model_uv ).rgb;
	vec3 material_ambient_color = material_diffuse_color * ambient_color;
	vec3 material_specular_color = texture2D( specular_texture, model_uv ).rgb;
	
	// Local normal, in tangent space. V tex coordinate is inverted because normal map is in TGA (not in DDS) for better quality
	vec3 tangent_texture_normal = normalize(texture2D( normal_texture, vec2(model_uv.x,-model_uv.y) ).rgb*2 - 1.0);
	
	// Normal of the computed fragment, in camera space , vec3 n = normalize( Normal_cameraspace );
	vec3 n = tangent_texture_normal;
	
	// Eye vector (towards the camera)
	vec3 E = normalize(camera_eye_direction);
	
	//color sums
	vec3 diffuse_color1;
	vec3 diffuse_color2;
	vec3 diffuse_color3;
	
	vec3 specular_color1;
	vec3 specular_color2;
	vec3 specular_color3;
	
	if( light_type1 == 1 )
	{
		// Material properties
		vec3 light_diff = material_diffuse_color * light_color1;
		vec3 light_spec = material_specular_color * specular_color1;
	
		// Distance to the light
		float distance = length( light_position1 - world_position );

		// Direction of the light (from the fragment to the light)
		vec3 l = normalize( camera_light_direction1 );

		// Cosine of the angle between the normal and the light direction, 
		// clamped above 0
		//  - light is at the vertical of the triangle -> 1
		//  - light is perpendicular to the triangle -> 0
		//  - light is behind the triangle -> 0
		float cosTheta = clamp( dot( n,l ), 0,1 );

		// Direction in which the triangle reflects the light
		vec3 R = reflect(-l,n);

		// Cosine of the angle between the Eye vector and the Reflect vector,
		// clamped to 0
		//  - Looking into the reflection -> 1
		//  - Looking elsewhere -> < 1
		float cosAlpha = clamp( dot( E,R ), 0,1 );
		
		//save color
		diffuse_color1 = light_diff * light_color1 * light_power1 * cosTheta / (distance*distance);
		specular_color1 = light_spec * light_color1 * light_power1 * pow(cosAlpha,5) / (distance*distance);
		
		// color = 
			// // Ambient : simulates indirect lighting
			// material_ambient_color +
			// // Diffuse : "color" of the object
			// material_diffuse_color * light_color1 * light_power1 * cosTheta / (distance*distance) +
			// // Specular : reflective highlight, like a mirror
			// material_specular_color * light_color1 * light_power1 * pow(cosAlpha,5) / (distance*distance);
		
	}
	if( light_type2 == 1 )
	{
		// Material properties
		vec3 light_diff = material_diffuse_color * light_color2;
		vec3 light_spec = material_specular_color * specular_color2;
	
		float distance = length( light_position2 - world_position );

		// Direction of the light (from the fragment to the light)
		vec3 l = normalize( camera_light_direction2 );

		// Cosine of the angle between the normal and the light direction, 
		// clamped above 0
		//  - light is at the vertical of the triangle -> 1
		//  - light is perpendicular to the triangle -> 0
		//  - light is behind the triangle -> 0
		float cosTheta = clamp( dot( n,l ), 0,1 );

		// Direction in which the triangle reflects the light
		vec3 R = reflect(-l,n);

		// Cosine of the angle between the Eye vector and the Reflect vector,
		// clamped to 0
		//  - Looking into the reflection -> 1
		//  - Looking elsewhere -> < 1
		float cosAlpha = clamp( dot( E,R ), 0,1 );
		
		//save color
		diffuse_color2 = light_diff * material_diffuse_color * light_color2 * light_power2 * cosTheta / (distance*distance);
		specular_color2 = light_spec * material_specular_color * light_color2 * light_power2 * pow(cosAlpha,5) / (distance*distance);
		
		// color = 
			// // Ambient : simulates indirect lighting
			// material_ambient_color +
			// // Diffuse : "color" of the object
			// material_diffuse_color * light_color2 * light_power2 * cosTheta / (distance*distance) +
			// // Specular : reflective highlight, like a mirror
			// material_specular_color * light_color2 * light_power2 * pow(cosAlpha,5) / (distance*distance);
		
	}
	if( light_type3 == 1 )
	{
		// Material properties
		vec3 light_diff = material_diffuse_color * light_color3;
		vec3 light_spec = material_specular_color * specular_color3;

		// Distance to the light
		float distance = length( light_position3 - world_position );

		// Direction of the light (from the fragment to the light)
		vec3 l = normalize( camera_light_direction3 );

		// Cosine of the angle between the normal and the light direction, 
		// clamped above 0
		//  - light is at the vertical of the triangle -> 1
		//  - light is perpendicular to the triangle -> 0
		//  - light is behind the triangle -> 0
		float cosTheta = clamp( dot( n,l ), 0,1 );

		// Direction in which the triangle reflects the light
		vec3 R = reflect(-l,n);

		// Cosine of the angle between the Eye vector and the Reflect vector,
		// clamped to 0
		//  - Looking into the reflection -> 1
		//  - Looking elsewhere -> < 1
		float cosAlpha = clamp( dot( E,R ), 0,1 );
		
		//save color
		diffuse_color3 = light_diff * material_diffuse_color * light_color3 * light_power3 * cosTheta / (distance*distance);
		specular_color3 = light_spec * material_specular_color * light_color3 * light_power3 * pow(cosAlpha,5) / (distance*distance);
		
		// color = 
			// // Ambient : simulates indirect lighting
			// material_ambient_color +
			// // Diffuse : "color" of the object
			// material_diffuse_color * light_color3 * light_power3 * cosTheta / (distance*distance) +
			// // Specular : reflective highlight, like a mirror
			// material_specular_color * light_color3 * light_power3 * pow(cosAlpha,5) / (distance*distance);
		
	}
	color = 
			// Ambient : simulates indirect lighting
			material_ambient_color +
			// Diffuse : "color" of the object
			(diffuse_color1 + diffuse_color2 + diffuse_color3) +
			// Specular : reflective highlight, like a mirror
			(specular_color1 + specular_color2 + specular_color3);
}
