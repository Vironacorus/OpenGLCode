#pragma once
#include <string>
#include "vendor/glm/source/glm.hpp"
#include "vendor/glm/source/gtc/matrix_transform.hpp"
#include "vendor/glm/source/gtc/type_ptr.hpp"
#include "glad/glad.h"


std::string read_file(const char* name);

typedef unsigned int uint;

struct shader_program
{
	uint id;

	uint get_uniform_location(const char* uniform_name);


	void set_uniform_mat4(uint location,const glm::mat4& value);
	void set_uniform_vec3(uint location, const glm::vec3& value);
	void set_uniform_int(uint location, int value);

	void attach_shader(uint shader);

	void link_program();

	void bind();

	shader_program();

	shader_program(uint vertex, uint fragment);
};

typedef shader_program program_t;

inline void compile_shader(uint shader, const char* content);

program_t program_from_file(const char* vert, const char* frag);