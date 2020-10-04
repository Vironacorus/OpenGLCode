#pragma once
typedef unsigned int uint;
struct ebo
{
	uint id = 0;
	ebo(const void* data, size_t size);
	ebo();
	void bind();
};