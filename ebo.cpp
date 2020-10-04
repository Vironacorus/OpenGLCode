#include "ebo.h"
#include "glad/glad.h"
ebo::ebo(const void* data, size_t size)
	{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

ebo::ebo() {		}

void ebo::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}
