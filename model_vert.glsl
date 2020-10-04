#version 420 core
layout(location=0) in vec3 pos;
layout(location=1) in vec2 tc;
layout(location=2) in vec3 normal;

layout(binding = 0, std140) uniform VP
{
mat4 vp;
};

uniform mat4 model;
out vec2 texcoords;

void main()
{
gl_Position = vp*model*vec4(pos,1);
texcoords = tc;
}