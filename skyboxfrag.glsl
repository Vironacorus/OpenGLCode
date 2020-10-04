#version 330 core
layout(location=0) out vec4 col;
in vec3 texcoords;

uniform samplerCube skybox;

void main()
{    
   col = texture(skybox, texcoords);
}