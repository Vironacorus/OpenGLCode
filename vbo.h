#pragma once
typedef unsigned int uint;
struct vbo
{

	uint id = 0;

	vbo(const void* data, size_t size);

	vbo();

	void bind();

};