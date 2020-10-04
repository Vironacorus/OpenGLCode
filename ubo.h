#pragma once
typedef unsigned int uint;
struct ubo
{
	uint id;
	uint buf_size;

	ubo(uint binding, size_t size);
	ubo(uint binding,size_t size,const void* data);

	void bind_range(uint i);
	void data(size_t offset,size_t size,const void* data);
	void bind();

};