#version 420 core
layout(location = 0) out vec4 col;
in vec2 texcoords;
uniform sampler2D tex;

void main()
{
col = texture(tex,texcoords);
}