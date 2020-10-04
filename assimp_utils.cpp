#include "assimp_utils.h"
#include "glad/glad.h"

std::unordered_map<std::string, assimp_texture> loaded_textures;

size_t mesh::vbo_size() const
{
	return vertices.size() * sizeof(assimp_vertex);
}

size_t mesh::ebo_size() const
{
	return indices.size() * sizeof(uint);
}

const void* mesh::ebo_data() const
{
	return &indices[0];
}

void mesh::draw_mesh()
{
	vertex_array_object.bind();
	auto iter = textures.begin();
	for (uint i = 0; i < textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, iter->id);
		++iter;
	}
	glDrawElements(GL_TRIANGLES,ebo_size(),GL_UNSIGNED_INT,0);
	glActiveTexture(GL_TEXTURE0);
}

void load_mesh_texture(std::vector<assimp_texture>& textures, aiMaterial* material, aiTextureType type)
{
	for (unsigned int i = 0; i < material->GetTextureCount(type); ++i)
	{
		aiString str;
		material->GetTexture(type, i, &str);
		std::string texname = str.C_Str();
		const auto& tex = loaded_textures.find(texname);
		bool is_loaded = (tex !=  loaded_textures.end());
		if (!is_loaded)
		{
			assimp_texture texture;
			texture.id = load_texture(str.C_Str(),false);
			texture.type = type;
			textures.push_back(texture);
			loaded_textures.insert({std::move(texname),texture });
		}
		else
		{
			assimp_texture texture;
			texture.id = tex->second.id;
			texture.type = type;
			textures.push_back(texture);
		}
	}
}


const void* mesh::vbo_data() const
{
	return &vertices[0];
}

mesh load_mesh(const aiScene* scene,uint index)
{
	load_flags flags;
	return load_mesh(&flags,scene,index);
}

mesh load_mesh(load_flags* load_data,const aiScene* scene,uint index)
{
	mesh mesh;
	auto* asmp_mesh = scene->mMeshes[index];

	bool hasnormals = (asmp_mesh->mNormals != nullptr);
	load_data->has_normals = hasnormals;
	bool hastexturecoords = (asmp_mesh->mTextureCoords[0]);
	load_data->has_texture_coords = hastexturecoords;

	for (int i = 0; i < asmp_mesh->mNumVertices; ++i)
	{
		float x = asmp_mesh->mVertices[i].x;
		float y = asmp_mesh->mVertices[i].y;
		float z = asmp_mesh->mVertices[i].z;
		float nx = 0;
		float ny = 0;
		float nz = 0;
		if (hasnormals)
		{
			nx = asmp_mesh->mNormals[i].x;
			ny = asmp_mesh->mNormals[i].y;
			nz = asmp_mesh->mNormals[i].z;
		}
		float tx = 0;
		float ty = 0;

		if (hastexturecoords)
		{
			tx = asmp_mesh->mTextureCoords[0][i].x;
			ty = asmp_mesh->mTextureCoords[0][i].y;
		}
		mesh.vertices.push_back({ glm::vec3(x,y,z),glm::vec2(tx,ty),glm::vec3(nx,ny,nz)});
	}

	for (unsigned int i = 0; i < asmp_mesh->mNumFaces; i++)
	{
		aiFace face = asmp_mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			mesh.indices.push_back(face.mIndices[j]);
	}

	aiMaterial* mat = scene->mMaterials[asmp_mesh->mMaterialIndex];
	load_mesh_texture(mesh.textures,mat, aiTextureType_DIFFUSE);

	mesh.vertex_array_object = vao(mesh.vbo_data(), mesh.vbo_size(), mesh.ebo_data(),
	mesh.ebo_size(), assimp_vertex::stride(),
	std::array<data, 3>{data{ GL_FLOAT,3 }, data{ GL_FLOAT,2 }, data{ GL_FLOAT,3 }}._Elems,
	3);
	return mesh;
}

scene load_scene(const char* path)
{
	scene r_scene;
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	for (uint i = 0; i < scene->mNumMeshes; ++i)
		r_scene.meshes.emplace_back(load_mesh(scene,i));
	return r_scene;
}

void scene::draw_scene()
{
	auto iterator = meshes.begin();
	for (uint i = 0; i < meshes.size(); ++i)
	{
		iterator->draw_mesh();
		++iterator;
	}
}
