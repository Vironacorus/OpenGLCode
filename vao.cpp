#include "vao.h"
#include "glad/glad.h"

uint glsize(uint datatype)
{
	{

		switch (datatype)
		{
		case GL_INT:
			return 4;
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		case GL_BYTE:
			return 1;
		}

		throw std::exception("Invalid type!");
		return -100;
	}
}

vao::vao(const void* vbodata, size_t vbosize, const void* ebodata, size_t ebosize,uint stride, data attributes[],uint attrib_count)
{
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
	vbo_in = vbo(vbodata, vbosize);
	ebo_in = ebo(ebodata, ebosize);
	uint previousoffset = 0;
	for (int i = 0; i < attrib_count; ++i)
	{
		glVertexAttribPointer(i, attributes[i].size, attributes[i].data_type, GL_FALSE, stride, (const void*)previousoffset);
		glEnableVertexAttribArray(i);
		previousoffset += glsize(attributes[i].data_type) * attributes[i].size;
	}
}

vao::vao(const void* vbodata, size_t vbosize, uint stride, data attributes[], uint attrib_count)
{
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
	vbo_in = vbo(vbodata, vbosize);
	uint previousoffset = 0;
	for (int i = 0; i < attrib_count; ++i)
	{
		glVertexAttribPointer(i, attributes[i].size, attributes[i].data_type, GL_FALSE, stride, (const void*)previousoffset);
		glEnableVertexAttribArray(i);
		previousoffset += glsize(attributes[i].data_type) * attributes[i].size;
	}
}

void vao::bind()
{
	glBindVertexArray(id);
}
