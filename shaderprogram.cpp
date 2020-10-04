#include "shaderprogram.h"
#include <fstream>
#include <sstream>
#include "glad/glad.h"
#include <iostream>

std::string read_file(const char* name)
{
	std::fstream file;
	file.open(name);
	std::stringstream sbuf;
	sbuf << file.rdbuf();
	file.close();
	return sbuf.str();
}

inline void compile_shader(uint shader, const char* content)
{
	glShaderSource(shader, 1, &content, 0);
	glCompileShader(shader);
	GLint success = false;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Shader compilation failed\n" << infoLog << std::endl;
	};
}

program_t program_from_file(const char* vert, const char* frag)
{
	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	auto strv = read_file(vert);
	const char* contentv = strv.c_str();
	auto strf = read_file(frag);
	const char* contentf = strf.c_str();
	compile_shader(vertex, contentv);
	compile_shader(fragment, contentf);
	program_t program;
	program.attach_shader(vertex);
	program.attach_shader(fragment);
	program.link_program();
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return program;
}

uint shader_program::get_uniform_location(const char* uniform_name)
{
	return glGetUniformLocation(id, uniform_name);
}

void shader_program::set_uniform_mat4(uint location, const glm::mat4& value)
{
	glUniformMatrix4fv(location, 1,GL_FALSE, glm::value_ptr(value));
}

void shader_program::set_uniform_vec3(uint location, const glm::vec3& value)
{
	glUniform3fv(location,1,glm::value_ptr(value));
}

void shader_program::set_uniform_int(uint location, int value)
{
	glUniform1i(location, value);
}

void shader_program::attach_shader(uint shader)
{
	glAttachShader(id, shader);
}

void shader_program::link_program()
{
	glLinkProgram(id);
}

void shader_program::bind()
{
	glUseProgram(id);
}

shader_program::shader_program()
{
	id = glCreateProgram();
}
shader_program::shader_program(uint vertex, uint fragment)
{
	id = glCreateProgram();
	attach_shader(vertex);
	attach_shader(fragment);
}