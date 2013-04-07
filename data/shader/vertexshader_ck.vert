#version 330 core

uniform vec3 fvLightPosition1;
uniform float fLightStrength1;
uniform mat4 matWorldInverse;
varying vec2 Texcoord;
varying vec3 ViewDirection;
varying vec3 LightDirection1;
varying vec4 LightDistMultiplier;

float getLengthSQR (vec3 vec)
{
	return(vec.x*vec.x+vec.y*vec.y+vec.z*vec.z);
}

void main( void )
{
	mat4 LightTransform= gl_ModelViewMatrix;
	LightTransform=LightTransform*matWorldInverse;
	gl_Position = ftransform();
	Texcoord    = gl_MultiTexCoord0.xy;
  
	vec4 fvObjectPosition = gl_ModelViewMatrix * gl_Vertex;
	vec4 fvLightPos1 = LightTransform * vec4(fvLightPosition1,1.0);
	vec3 fvViewDirection  =  - fvObjectPosition.xyz;
	vec3 fvLightDirection1 = (fvLightPos1.xyz - fvObjectPosition.xyz);
	LightDistMultiplier[0]=1.0/(getLengthSQR (fvLightDirection1)/(fLightStrength1*10000.0));
	vec3 fvNormal         = gl_NormalMatrix * gl_Normal;
	vec3 fvTangent   = -vec3(abs(gl_Normal.y) + abs(gl_Normal.z), abs(gl_Normal.x), 0);
	vec3 fvBinormal =cross(fvTangent,gl_Normal);
	fvTangent=gl_NormalMatrix*cross(fvBinormal,gl_Normal);
	fvBinormal=gl_NormalMatrix*fvBinormal;
	ViewDirection.x  = dot( fvTangent, fvViewDirection );
	ViewDirection.y  = dot( fvBinormal, fvViewDirection );
	ViewDirection.z  = dot( fvNormal, fvViewDirection );
	LightDirection1.x  = dot( fvTangent, fvLightDirection1.xyz );
	LightDirection1.y  = dot( fvBinormal, fvLightDirection1.xyz );
	LightDirection1.z  = dot( fvNormal, fvLightDirection1.xyz );
}