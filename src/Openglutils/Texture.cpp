#include "Texture.h"

//TODO Better setting unitg
  //Initialize the texture managment structure
  void initTextRess (TextureResource &tex_resource, GLuint p_texture_id, int p_unit )
    {
        glGenSamplers(1, &tex_resource.sampler_id);
        tex_resource.texture_id = p_texture_id;
        tex_resource.unit = p_unit;
    }


//TODO Let user set unit here rather than prior
void bindTexture(const TextureResource &tex_resource, const GLuint & program, const char *uniform_name)
{
    glActiveTexture(GL_TEXTURE0 + tex_resource.unit);
    glBindTexture(GL_TEXTURE_2D, tex_resource.texture_id);
    glBindSampler(tex_resource.unit, tex_resource.sampler_id);
    // Assuming shader_program is the active program and uniform_name is the texture uniform name
    int unifrm_loc = glGetUniformLocation(program, uniform_name);
    glUniform1i(unifrm_loc, tex_resource.unit);
}

void release( TextureResource &tex_resource)
{
    glActiveTexture(GL_TEXTURE0 + tex_resource.unit);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindSampler(tex_resource.unit, 0);
}

GLuint makeTextureMat(const int unit,
                      const Mat<uint8_t> &im)
{
    if (im.getCols() == 0 && im.getRows() == 0)
    {
        std::cerr << " Image has no columns and rows (both are zero)." << std::endl;
        return 0;
    }
    int channels = im.getChannels();

    if (channels < 1 || channels > 4)
    {
        std::cerr << "Invalid number of channels. Must be between 1 and 4." << std::endl;
        return 0;
    }
    GLenum format = GL_RGB;
    GLenum texel_type = GL_RGB;

    switch (channels)
    {
    case 1:
        format = GL_RED;
        break;
    case 2:
        format = GL_RG;
        break;
    case 3:
        format = GL_RGB;
        if (im.getCols() % 3 != 0)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        }
        break;
    case 4:
        format = GL_RGBA;
        texel_type = GL_RGBA;
        break;
    default:
        break;
    }
    GLenum data_type = GL_UNSIGNED_BYTE;
    GLuint texture;
    glGenTextures(1, &texture);
    if (glGetError() != GL_NO_ERROR)
    {
        std::cerr << "Failed to generate texture." << std::endl;
        return 0;
    }
    // TODO NO use here remove
    glActiveTexture(GL_TEXTURE0 + unit);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, texel_type, im.getCols(), im.getRows(), 0,
                 format, data_type, im.getData());
    if (glGetError() != GL_NO_ERROR)
    {
        std::cerr << "Failed to create texture image." << std::endl;
        return 0;
    }

    // prefiltre la texture
    // glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); // BY default this use a MIPMAP, hence yhou need to define the two parameter LEVEL
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // LImit the number of mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
    std::cout<<"Makein5"<<std::endl;

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error after making texture: " << error << std::endl;
        return 0;
    }

    return texture;
}

GLuint read_texture(const int unit,
                    const char *filename, Mat<uint8_t> &img, int nbchannels)
{

    img = loadImg(filename, true, nbchannels);

    GLuint texture = makeTextureMat(unit, img);

    return texture;
}

void freeTexture(TextureResource &tex_resource)
{
    glDeleteTextures(1, &tex_resource.texture_id);
    glDeleteSamplers(1, &tex_resource.sampler_id);
}

void freeTexture(GLuint &tex_resource)
{
    glDeleteTextures(1, &tex_resource);
}


