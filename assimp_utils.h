#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "vendor/glm/source/glm.hpp"
#include "vendor/glm/source/gtc/matrix_transform.hpp"
#include "vendor/glm/source/gtc/type_ptr.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "texture.h"
#include "vao.h"


typedef unsigned int uint;

struct assimp_texture;

extern std::unordered_map<std::string,assimp_texture> loaded_textures;

struct assimp_vertex
{
	glm::vec3 pos;
	glm::vec2 texcoord;
	glm::vec3 normal;
	constexpr static uint stride()
	{
		return 8 * sizeof(float);
	}
};

struct assimp_texture
{
	uint id;
	aiTextureType type;
};

struct mesh;

struct scene
{
	std::vector<mesh> meshes;
	void draw_scene();
};

struct mesh
{

	std::vector<assimp_vertex> vertices;
	std::vector<assimp_texture> textures;
	std::vector<uint> indices;
	vao vertex_array_object;
	size_t vbo_size() const;
	size_t ebo_size() const;
	const void* vbo_data() const;
	const void* ebo_data() const;
	void draw_mesh();
};

struct load_flags { bool has_texture_coords = false; bool has_normals = false;};

void load_mesh_texture(std::vector<assimp_texture>& texture,aiMaterial* material,aiTextureType type);
mesh load_mesh(const aiScene* scene,uint index = 0);
mesh load_mesh(load_flags* load_data,const aiScene* scene, uint index = 0);
scene load_scene(const char* path);