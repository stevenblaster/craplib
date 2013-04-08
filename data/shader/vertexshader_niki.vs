#version 330

//layout (std140) uniform Matrices {
//    mat4 pvm; //projection view matrix
//};

//Uniform Matrix
uniform mat4 mat4_pvm; //projection view matrix
uniform mat4 mat4_viewModel;
uniform mat3 mat3_normal;

//Uniform Lights
uniform vec4 vec4_lightPos;

in vec4 position;	//in local Space
in vec3 normal; 	//in local Space

out Data {
	vec3 vec3_normal;
	vec3 vec3_eye;
	vec3 vec3_lightDir;
} DataOut;

void main()
{
	vec4 pos = mat4_viewModel * position;
	DataOut.vec3_normal = normalize(/*mat3_normal * */normal);
	DataOut.vec3_lightDir = vec3(vec4_lightPos - pos);
	DataOut.vec3_eye = vec3(-pos);
	
    // transform the vertex coordinates
    gl_Position = mat4_pvm * position; 
}