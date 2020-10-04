#include "vbo.h"
#include "glad/glad.h"

vbo::vbo(const void* data, size_t size)
{
glGenBuffers(1, &id);
glBindBuffer(GL_ARRAY_BUFFER, id);
glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

vbo::vbo() {	}

void vbo::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}
