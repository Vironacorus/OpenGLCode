#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 lspace_mat;
uniform mat4 models[2];

void main()
{
    gl_Position = lspace_mat * models[int(gl_InstanceID)] * vec4(aPos, 1.0);
}  