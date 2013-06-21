#version 330 core

// should be done otherwise
#define MAX_LIGHTS 3

// input
in vec2 modelspace_uv;
in vec3 worldspace_position;
in vec3 cameraspace_eye_direction;
in vec3 cameraspace_light_direction[MAX_LIGHTS];
in vec3 cameraspace_normal;
in vec3 tangentspace_eye_direction;
in vec3 tangentspace_light_direction[MAX_LIGHTS];
in vec4 shadow_coordinates;

// Ouput data
out vec3 color;

//uniforms
uniform sampler2D diffuse_texture;
uniform sampler2D normal_texture;
uniform sampler2D height_texture;

uniform float ambient_power;

uniform vec3 light_position[MAX_LIGHTS];
uniform vec3 light_direction[MAX_LIGHTS];
uniform int light_type[MAX_LIGHTS];
uniform int light_state[MAX_LIGHTS];

uniform float light_power[MAX_LIGHTS];
uniform int light_specular_type[MAX_LIGHTS];
uniform float light_specular_lobe[MAX_LIGHTS];
uniform vec3 light_color[MAX_LIGHTS];

uniform int normal_mapping_on;
uniform int displacement_on = 1;
uniform int selfshadowing_on = 1;

uniform sampler2DShadow shadow_map;
uniform mat4 view_matrix4x4;
uniform int shadow_mapping_on;

uniform float displacement_steps = 10;
uniform float displacement_refinement_steps = 5;
uniform float displacement_uv_factor = 3;

//displacement
void do_displace_uv(out vec2 displaced_uv)
{
	displaced_uv = modelspace_uv;
	float displSteps = displacement_steps;
	float refinSteps = displacement_refinement_steps;

	float h				= 1.0f;
	vec2  dUV			= -(tangentspace_eye_direction / displSteps / displacement_uv_factor).xy;
	float previous_hit	= 0;
	float hit_h			= 0;
	float stepSize		= 1.0f / displSteps;
	vec2  tUV			= modelspace_uv;
	float hit_step		= 0;
   
	for (int i = 0; i < displSteps; ++i) 
	{
		h  -= stepSize;
		tUV += dUV;
		float h_tex = texture2D(height_texture, tUV).r;
		float is_first_hit = clamp((h_tex - h - previous_hit) * 4999999, 0, 1);

		// equivalent to: if ( (h_tex < h) && !prev_hit )
		hit_h		 += is_first_hit * h; 
		hit_step	 += is_first_hit * i;
		previous_hit += is_first_hit;
	}
	displaced_uv += ((hit_step + 1) * dUV);

	// refinement steps:
	h			 = hit_h + stepSize;	// start one location above the first hit
	dUV			 /= refinSteps;			// change displacement depth for refinement
	previous_hit = 0;					// reset already-hit variable
	hit_h		 = 0;					// reset hit height
	hit_step	 = 0;					// reset hit step
	tUV			 = modelspace_uv;		// reset step uv coords

	stepSize /= refinSteps;
	for(int i = 0; i < refinSteps; ++i)
	{
		h  -= stepSize;
		tUV += dUV;
		float h_tex			= texture2D(height_texture, tUV).r;
		float is_first_hit	= clamp((h_tex - h - previous_hit) * 4999999, 0, 1);

		hit_step	 += is_first_hit * i;
		previous_hit += is_first_hit;
	}
	displaced_uv += ((hit_step + 1) * dUV);		// change UV coords according to our refinement hit
}

vec2 poissonDisk[16] = vec2[]( 
   vec2( -0.94201624, -0.39906216 ), 
   vec2( 0.94558609, -0.76890725 ), 
   vec2( -0.094184101, -0.92938870 ), 
   vec2( 0.34495938, 0.29387760 ), 
   vec2( -0.91588581, 0.45771432 ), 
   vec2( -0.81544232, -0.87912464 ), 
   vec2( -0.38277543, 0.27676845 ), 
   vec2( 0.97484398, 0.75648379 ), 
   vec2( 0.44323325, -0.97511554 ), 
   vec2( 0.53742981, -0.47373420 ), 
   vec2( -0.26496911, -0.41893023 ), 
   vec2( 0.79197514, 0.19090188 ), 
   vec2( -0.24188840, 0.99706507 ), 
   vec2( -0.81409955, 0.91437590 ), 
   vec2( 0.19984126, 0.78641367 ), 
   vec2( 0.14383161, -0.14100790 ) 
);

// Returns a random number based on a vec3 and an int.
float random(vec3 seed, int i){
	vec4 seed4 = vec4(seed,i);
	float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
	return fract(sin(dot_product) * 43758.5453);
}

void main()
{
	//tangentspace_eye_direction = cross(tangentspace_eye_direction,cameraspace_normal);
	//tangentspace_eye_direction *= -1;
	// displacement
	vec2 final_uv = modelspace_uv;
	if( displacement_on == 1 ) 
	{
		do_displace_uv(final_uv);
	}
	
	// Material properties
	vec3 material_diffuse_color = texture2D( diffuse_texture, final_uv ).rgb;
	vec3 tangentspace_texture_normal = texture2D( normal_texture, final_uv).rgb * 2.0 - 1.0;
	
	//colors
	color = vec3(0,0,0);
	vec3 colors[MAX_LIGHTS];
	
	//for each light
	for( int i = 0; i< MAX_LIGHTS; ++i )
	{
		colors[i] = vec3(0,0,0);
		
		if( light_state[i] == 1 ) // is turned on
		{
			float distanceSqr = 0.0;
			if( light_type[i] == 0 ) //directional light
			{
				vec3 fragmentToLight = (light_position[i] - worldspace_position);
				distanceSqr = dot(fragmentToLight, fragmentToLight);
			}
			else if( light_type[i] == 1 ) //point light
			{
				distanceSqr = 1;
			}
			
			vec3 N = normalize(cameraspace_normal);			// Normal of the computed fragment
			vec3 L = normalize(cameraspace_light_direction[i]);	// Direction of the light (from the fragment to the light)
			vec3 V = normalize(cameraspace_eye_direction);	// Eye vector (towards the camera)
					
			if( normal_mapping_on == 1 )
			{
				N = normalize(tangentspace_texture_normal);			// Normal of the computed fragment
				L = normalize(tangentspace_light_direction[i]);	// Direction of the light (from the fragment to the light)
				V =  normalize(tangentspace_eye_direction);	// Eye vector (towards the camera)	
			}
			
			vec3 R = vec3(0, 0, 0);
			vec3 H = vec3(0, 0, 0);
			
			if( light_specular_type[i] == 0 ) 
			{
				R = normalize(2 * dot(N, L) * N - L);		// Direction in which the triangle reflects the light. R = 2 * (N.L) * N ? L
			}
			else if( light_specular_type[i] == 1 ) 
			{
				H = normalize(V + L);
			}
			
			float cosTheta = clamp(dot(N, L), 0, 1);
			float shadow = 1.0;
			
			if( selfshadowing_on == 1 )
			{
				shadow = clamp(4 * cosTheta, 0, 1);
			}
			
			float cosAlpha = 0.0;
			
			if( light_specular_type[i] == 0) 
			{
				cosAlpha = clamp(dot(R, V), 0, 1);
			}
			else if( light_specular_type[i] == 1 )
			{
				cosAlpha = clamp(dot(N, H), 0, 1);
			}
			
			vec3 ambient	= ambient_power * material_diffuse_color;
			vec3 diffuse	= material_diffuse_color * light_color[i] * light_power[i];
			vec3 specular	= light_color[i] * light_power[i];
			
			float bias = 0.005;
			float visibility=1.0;
			
			if( shadow_mapping_on == 1 )
			{
				for (int i=0;i<4;i++)
				{
					int index = i;
					//  - A random sample, based on the pixel's screen location. 
					//    No banding, but the shadow moves with the camera, which looks weird.
					// int index = int(16.0*random(gl_FragCoord.xyy, i))%16;
					//  - A random sample, based on the pixel's position in world space.
					//    The position is rounded to the millimeter to avoid too much aliasing
					// int index = int(16.0*random(floor(Position_worldspace.xyz*1000.0), i))%16;
						
					// being fully in the shadow will eat up 4*0.2 = 0.8
					// 0.2 potentially remain, which is quite dark.
					visibility -= 0.2*(1.0-texture( shadow_map, vec3(shadow_coordinates.xy + poissonDisk[index]/700.0,  (shadow_coordinates.z-bias)/shadow_coordinates.w) ));
				}
			}
			
			colors[i] = ambient + visibility * shadow * (diffuse * cosTheta + specular * pow(cosAlpha, light_specular_lobe[i])) / distanceSqr;	
		}		
	}
	for( int j = 0; j< MAX_LIGHTS; ++j )
	{
		color += colors[j];
	}
}