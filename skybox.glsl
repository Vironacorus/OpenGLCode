#version 330 core
layout (location = 0) in vec3 pos;
out vec3 texcoords;
uniform mat4 proj;
uniform mat4 model;
uniform mat4 view;

void main()
{
    texcoords = (pos*2);
    vec4 temp_pos = proj * view* model * vec4(pos, 1.0);
    gl_Position = temp_pos.xyww;
}  