#version 330 core

uniform vec4 fvAmbient;
uniform vec4 fvLight1Color;

uniform float fSpecularPower;
uniform float fSpecularStrength;
uniform float fBumpStrength;

uniform sampler2D baseMap;
uniform sampler2D bumpMap;

varying vec2 Texcoord;
varying vec3 ViewDirection;
varying vec3 LightDirection1;
varying vec4 LightDistMultiplier;

void main( void )
{

vec3  fvLightDirection1 = normalize( LightDirection1 );

vec3  fvNormal         = texture2D( bumpMap, Texcoord ).yxz;
fvNormal.xy*=2.0;
fvNormal.xy-=1.0;

fvNormal=(vec3(0.0,0.0,1.0)-fvNormal)*fBumpStrength+fvNormal;

fvNormal=normalize(fvNormal);

float fNDotL1           = max(dot(fvNormal, fvLightDirection1),0.0)-0.1; 

vec3  fvReflection1     = normalize( ( ( 2.0 * fvNormal )  ) - fvLightDirection1 ); 

vec3  fvViewDirection  = normalize( ViewDirection );
float fRDotV1          = max( 0.0, dot( fvReflection1, fvViewDirection ) );

vec4  fvBaseColor      = texture2D( baseMap, Texcoord );

vec4  fvTotalAmbient   = fvAmbient * fvBaseColor;

vec4  fvTotalDiffuse   = fvLight1Color * fNDotL1* fvBaseColor*LightDistMultiplier[0];
vec4  fvTotalSpecular  = fNDotL1*fvLight1Color * ( pow( fRDotV1, fSpecularPower ) )*LightDistMultiplier[0];

vec4 color=( fvTotalAmbient + fvTotalDiffuse+ (fvTotalSpecular*fSpecularStrength));
if(color.r>1.0){color.gb+=color.r-1.0;}
if(color.g>1.0){color.rb+=color.g-1.0;}
if(color.b>1.0){color.rg+=color.b-1.0;}
gl_FragColor = color;

}