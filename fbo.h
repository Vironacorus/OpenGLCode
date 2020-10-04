#pragma once
typedef unsigned int uint;
struct fbo
{
	uint id;
	fbo();
	uint texture_attachment(uint attachment, uint type,uint format,uint w, uint h);
	uint texture_attachment(uint attachment, uint type, uint format,uint internalformat, uint w, uint h);
	uint renderbuffer_attachment(uint attachment, uint type, uint w, uint h);
	void bind();
	void unbind();
};

