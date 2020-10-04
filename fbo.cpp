#include "fbo.h"
#include "glad/glad.h"
fbo::fbo()
{
	glGenFramebuffers(1,&id);
	glBindFramebuffer(GL_FRAMEBUFFER,id);
}

uint fbo::texture_attachment(uint attachment,uint type,uint format,uint w,uint h)
{
	return texture_attachment(attachment,type,format,format,w,h);
}

uint fbo::texture_attachment(uint attachment, uint type, uint format, uint internalformat, uint w, uint h)
{
	uint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexImage2D(GL_TEXTURE_2D, 0, internalformat, w, h, false, format, type, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture, 0);
	return texture;
}

uint fbo::renderbuffer_attachment(uint attachment,uint type,uint w,uint h)
{
	uint  rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, type , w, h);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, rbo);
	return rbo;
}

void fbo::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER,id);
}

void fbo::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER,0);
}
