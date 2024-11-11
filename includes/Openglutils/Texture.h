#ifndef _TEXTURE_H
#define _TEXTURE_H
// https://www.khronos.org/opengl/wiki/Common_Mistakes
#include "glcore.h"
#include <cstdio>
#include <algorithm>
#include "Imloader.h"
// TODO Separate into cpp and h file
struct TextureResource
{
    GLuint texture_id;
    GLuint sampler_id;
    int unit;
    TextureResource() = default;
};
// Initialize the texture managment structure
void initTextRess(TextureResource &texResource, GLuint p_texture_id, int p_unit = 0);

void bindTexture(const TextureResource &texResource, const GLuint &program, const char *uniform);

void release(TextureResource &texResource);

void freeTexture(TextureResource &texResource);
void freeTexture(GLuint &texResource);

enum class TextType
{
    MT_UC,
    MT_UINT,
    MT_INT,
    MT_FLOAT,
};


GLuint makeTextureMat(const int unit,
                      const Mat<uint8_t> &im)
;
GLuint read_texture(const int unit,
                    const char *filename, Mat<uint8_t> &img, int nbchannels = 0);
#endif
