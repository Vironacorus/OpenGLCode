#version 420 core
layout(location=0) in vec3 pos;
layout(location=1) in vec2 texcoords;
layout(location=2) in vec3 in_norm;
out vec2 frag_texCoords;
out vec3 normal;
out vec3 fragpos;
out vec4 fragposlightspace;


uniform mat4 models[2];
uniform mat4 light_space_matrix;

layout(std140,binding = 0) uniform VP
{
mat4 vp;
};

void main()
{
int index = gl_InstanceID;
frag_texCoords = texcoords;
fragpos = vec3(models[int(index)] * vec4(pos, 1.0));
normal = mat3(transpose(inverse(models[int(index)]))) * in_norm;
fragposlightspace = light_space_matrix * vec4(fragpos, 1.0);
gl_Position = vp*models[int(index)]*vec4(pos,1);
}