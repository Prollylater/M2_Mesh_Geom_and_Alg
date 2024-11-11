#ifndef _BUFFERS_H
#define _BUFFERS_H
#include "glcore.h"
#include <vector>
#include "Vec.h"
#include "Vertices.h"
#include "Texture.h"

// Structure holding a vao and it's attached vbo and ebo
struct BufferIDsGroups
{
public:
    GLuint m_vao_id, m_vbo_id, m_ebo_id;
    TextureResource mesh_texture;
    std::vector<GLuint> sub_vbo; // Vbo related to additional location

    int m_count;
    BufferIDsGroups() = default;
    BufferIDsGroups(GLuint vao_id, GLuint vbo_id, GLuint ebo_id);
    BufferIDsGroups(GLuint vao_id, GLuint vbo_id, GLuint ebo_id, int count);
    void linkTexture(TextureResource &tex_resource, const GLuint &texture_id)
    {
        initTextRess(tex_resource, texture_id, 0);
    };

    GLuint getVao() const;
    void addVBO(GLuint);

    int getCount();

    friend void freeBuffers(BufferIDsGroups &bufferid);

private:
    void zeros();
};

// Friend function of BufferIDsGroups
void freeBuffers(BufferIDsGroups &bufferid);

// TODO REBIND FUNCTION
BufferIDsGroups createBuffers(const std::vector<Vec<float>> &verticestab, const std::vector<GLuint> &indices = {},
                              const std::vector<Vec<float>> &texcoords = {});
BufferIDsGroups createBuffers(const std::vector<Vertices> &verticestab, const std::vector<GLuint> &indices = {},
                              const std::vector<Vertices> &normals = {},
                              const std::vector<Vertices> &texcoords = {});


void updateBuffer(const BufferIDsGroups &bufferGroup, 
                  const std::vector<Vertices> &new_verticestabs = {}, 
                  const std::vector<GLuint> &new_indices = {},
                  const std::vector<Vertices> &new_normals = {},
                  const std::vector<Vertices> &new_texcoords = {});

// Create and additional FBO with a binded texture
GLuint createFBO(TextureResource &texress);
void useFbo(GLuint fbo);
void attachFbo(GLuint fbo, TextureResource &texress);
#endif
