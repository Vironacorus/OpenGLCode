#version 420 core
layout(location=0) in vec3 pos;
layout(location=1) in vec2 texcoords;
layout(location=2) in vec3 in_norm;
uniform mat4 models[2];

layout(std140,binding = 0) uniform VP
{
mat4 vp;
};

void main()
{
int index = gl_InstanceID;
gl_Position = vp*models[int(index)]*vec4(pos,1);
}