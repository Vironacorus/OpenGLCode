#include "ubo.h"
#include "glad/glad.h"

ubo::ubo(uint binding, size_t size) : buf_size(size)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_UNIFORM_BUFFER, id);
	glBufferData(GL_UNIFORM_BUFFER, size, 0, GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, id, 0, size);
}

ubo::ubo(uint binding, size_t size, const void* data) : buf_size(size)
{
	glGenBuffers(1,&id);
	glBindBuffer(GL_UNIFORM_BUFFER,id);
	glBufferData(GL_UNIFORM_BUFFER,size,data,GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER,0,id,0,size);
}

void ubo::bind_range(uint i)
{
	glBindBufferRange(GL_UNIFORM_BUFFER,i,id,0,buf_size);
}

void ubo::data(size_t offset, size_t size, const void* data)
{
	glBufferSubData(GL_UNIFORM_BUFFER,offset,size,data);
}

void ubo::bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER,id);
}
