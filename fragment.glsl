#version 420 core
layout(location=0) out vec4 col;
uniform sampler2D image;
uniform vec3 lightpos;
uniform sampler2D shadowMap;
in vec2 frag_texCoords;
in vec3 normal;
in vec3 fragpos;
in vec4 fragposlightspace;

float calcShadow(vec4 fpos_ls)
{
	vec3 projCoords = fpos_ls.xyz / fpos_ls.w;
	projCoords = (projCoords * 0.5 + 0.5);
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	vec3 ldir = normalize(lightpos - fragpos);
	float currentDepth = projCoords.z;
	float bias = max(0.05 * (1.0 - dot(normal, ldir)), 0.005);
	float shadow = (currentDepth-bias) > closestDepth  ? 1.0 : 0.0;
	return shadow*0.5;
}


void main()
{
const vec4 lightcol = vec4(1,0,0,1);
const float diffuse_strength = 0.21;
const float ambient_stength = 0.06;
col = texture(image,frag_texCoords);
vec3 nnorm = normalize(normal);
vec3 ldir = normalize(lightpos-fragpos);
vec3 diffuse = vec3(   diffuse_strength*max(dot(nnorm,ldir),0)   );

col=vec4((diffuse+vec3(ambient_stength))*col.rgb,1);
col = vec4(col.rgb*((1-calcShadow(fragposlightspace))),1);
}