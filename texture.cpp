#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image/stb_image.h"
#include "glad/glad.h"

uint load_texture(const char* filename,bool flip)
{
	stbi_set_flip_vertically_on_load(flip);
	uint texture;
	int width, height, channels;
	unsigned char* img_data = stbi_load(filename, &width, &height, &channels, NULL);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	if (channels == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, TEX_INTERNAL_ALPHA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, TEX_INTERNAL, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(img_data);
	return texture;
}

uint load_cubemap(const char** filenames, bool flip)
{
	stbi_set_flip_vertically_on_load(flip);

	uint cubemap;
	glGenTextures(1, &cubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);

	for (int i = 0; i < 6; ++i)
	{
		int width, height, channels;
		unsigned char* data = stbi_load(filenames[i], &width, &height, &channels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, TEX_INTERNAL, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	stbi_set_flip_vertically_on_load(1);
	return cubemap;
}