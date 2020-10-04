#pragma once
#include "vbo.h"
#include "ebo.h"
#include <array>

struct data
{
	uint data_type;
	uint size;
};

uint glsize(uint datatype);

struct vao
{
	vbo vbo_in;
	ebo ebo_in;
	uint id{ 0 };
	vao(const void* vbodata, size_t vbosize, const void* ebodata, size_t ebosize, uint stride, data attributes[],uint attrib_count);
	vao(const void* vbodata, size_t vbosize, uint stride, data attributes[], uint attrib_count);
	vao() = default;
	void bind();
};