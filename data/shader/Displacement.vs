#version 410 core

layout (location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec2 vertexUV;
layout (location = 2) in vec3 vertexNormal_modelspace;

uniform mat4 M;

out vec3 Position_cs_worldspace;
out vec2 UV_cs;
out vec3 Normal_cs_worldspace;

void main()
{
    Position_cs_worldspace = (M * vec4(vertexPosition_modelspace, 1.0)).xyz;
    UV_cs = vertexUV;
    Normal_cs_worldspace = (M * vec4(vertexNormal_modelspace, 0.0)).xyz;
} 