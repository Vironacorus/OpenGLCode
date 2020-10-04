#version 420 core
layout(location=0) out vec4 col;
in vec2 texcoords;
uniform sampler2D screenimage;

void main()
{
	col =  texture(screenimage,texcoords);
}