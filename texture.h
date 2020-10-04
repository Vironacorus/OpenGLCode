#pragma once

typedef unsigned int uint;

#define USE_GAMMA_CORRECTION
#ifdef USE_GAMMA_CORRECTION
#define ENABLE_GAMMA_CORRECTION glEnable(GL_FRAMEBUFFER_SRGB)
#define TEX_INTERNAL GL_SRGB
#define TEX_INTERNAL_ALPHA GL_SRGB_ALPHA
#else
#define ENABLE_GAMMA_CORRECTION
#define TEX_INTERNAL GL_RGB
#define TEX_INTERNAL_ALPHA GL_RGBA
#endif

uint load_texture(const char* filename,bool flip = true);

uint load_cubemap(const char** filenames,bool flip = false);