#include "Buffers.h"

// Structure holding a vao and it's attached vbo and ebo

BufferIDsGroups::BufferIDsGroups(GLuint vao_id, GLuint vbo_id, GLuint ebo_id) : m_vao_id(vao_id), m_vbo_id(vbo_id), m_ebo_id(ebo_id) {};
BufferIDsGroups::BufferIDsGroups(GLuint vao_id, GLuint vbo_id, GLuint ebo_id, int count) : m_vao_id(vao_id), m_vbo_id(vbo_id), m_ebo_id(ebo_id), m_count(count) {};
void BufferIDsGroups::zeros()
{
    m_vao_id = 0;
    m_vbo_id = 0;
    m_ebo_id = 0;
}

GLuint BufferIDsGroups::getVao() const
{
    return m_vao_id;
}

int BufferIDsGroups::getCount()
{
    return m_count;
}
BufferIDsGroups createBuffers(const std::vector<Vec<float>> &verticestab, const std::vector<GLuint> &indices,
                              const std::vector<Vec<float>> &texcoords)
{
    if (verticestab.size() <= 0)
    {
        // Simply add Exception here
        return BufferIDsGroups();
    }

    GLuint vao, vbo, vbotex, ebo;
    // Generate all vertex
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // Bind vao in which everything will be stored
    glBindVertexArray(vao);

    // Bind Vertex Buffer object
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticestab.size() * sizeof(Vec<float>), verticestab.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void *)0);
    glEnableVertexAttribArray(0);

    // Bind Texturecoordinate
    if (texcoords.size() && texcoords.size() == verticestab.size())
    {
        glGenBuffers(1, &vbotex);
        glBindBuffer(GL_ARRAY_BUFFER, vbotex);
        glBufferData(GL_ARRAY_BUFFER, texcoords.size() * sizeof(Vec<float>), texcoords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (const void *)0);
        glEnableVertexAttribArray(1);
    }

    // Create Read to mesh

    if (indices.size())
    {
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }
    glBindVertexArray(0);
    GLenum error = glGetError();

    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error during vertex buffer initialization: " << error << std::endl;
        return BufferIDsGroups(0, 0, 0, 0);
    }
    BufferIDsGroups return_buff = BufferIDsGroups(vao, vbo, ebo, indices.size());
    if (vbotex)
    {
        return_buff.addVBO(vbotex);
    }
    return return_buff;
}

BufferIDsGroups createBuffers(const std::vector<Vertices> &verticestab, const std::vector<GLuint> &indices,
                              const std::vector<Vertices> &normals,
                              const std::vector<Vertices> &texcoords)
{

    //.....
    auto convertToUsableFormat = [](const std::vector<Vertices> &vertices)
    {
        std::vector<float> vector;
        for (const auto &vertex : vertices)
        {
            vector.push_back(vertex.x);
            vector.push_back(vertex.y);
            vector.push_back(vertex.z);
        }
        return vector;
    };

    if (verticestab.size() <= 0)
    {
        std::cout << "Empty Vertices in the passed mesh" << std::endl;
        return BufferIDsGroups();
    }

    GLuint vao, vbo, vbo_tex, vbo_norm, ebo;
    // Generate all vertex
    glGenVertexArrays(1, &vao);

    // Bind vao in which everything will be stored
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);

    // Bind Vertex Buffer object
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticestab.size() * sizeof(float) * 3, (convertToUsableFormat(verticestab)).data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void *)0);

    glEnableVertexAttribArray(0);
    // Bind Normals
    if (!normals.empty())
    {
        glGenBuffers(1, &vbo_norm);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_norm);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float) * 3, (convertToUsableFormat(normals)).data(), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const void *)0);
        glEnableVertexAttribArray(1);
    }

    // Bind Texturecoordinate
    // Despite using UV, Vertices class use 3
    if (!texcoords.empty())
    {
        glGenBuffers(1, &vbo_tex);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_tex);
        glBufferData(GL_ARRAY_BUFFER, texcoords.size() * sizeof(float) * 3, (convertToUsableFormat(texcoords)).data(), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (const void *)0);
        glEnableVertexAttribArray(2);
    }

    // Create Read to mesh

    if (indices.size())
    {
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_DYNAMIC_DRAW);
    }
    glBindVertexArray(0);
    GLenum error = glGetError();

    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error during vertex buffer initialization: " << error << std::endl;
        return BufferIDsGroups(0, 0, 0, 0);
    }

    BufferIDsGroups return_buff = BufferIDsGroups(vao, vbo, ebo, indices.size());
    if (vbo_norm)
    {
        return_buff.addVBO(vbo_norm);
    }
    if (vbo_tex)
    {
        return_buff.addVBO(vbo_tex);
    }
    std::cout << "Return " << vbo << " " << vbo_norm << "  " << vbo_tex << " " << vao << std::endl;
    return return_buff;
}

void updateBuffer(const BufferIDsGroups &bufferGroup,
                  const std::vector<Vertices> &new_verticestabs,
                  const std::vector<GLuint> &new_indices,
                  const std::vector<Vertices> &new_normals,
                  const std::vector<Vertices> &new_texcoords)
{
    // Bind the VAO
    glBindVertexArray(bufferGroup.m_vao_id);
    auto convertToUsableFormat = [](const std::vector<Vertices> &vertices)
    {
        std::vector<float> vector;
        for (const auto &vertex : vertices)
        {
            vector.push_back(vertex.x);
            vector.push_back(vertex.y);
            vector.push_back(vertex.z);
        }
        return vector;
    };

    if (!new_verticestabs.empty())
    {

        glNamedBufferSubData(bufferGroup.m_vbo_id, 0, new_verticestabs.size() * sizeof(float) * 3,
                             (convertToUsableFormat(new_verticestabs)).data());
                             
    }

    // Update Vertex Buffer if new vertices are provided
    if (!new_indices.empty() && bufferGroup.m_ebo_id != 0)
    {
        // Read data from the buffer

        glNamedBufferSubData(bufferGroup.m_ebo_id, 0, new_indices.size() * sizeof(GLuint), new_indices.data());

      
    }
    // Update Normal Buffer
    if (!new_normals.empty() && !bufferGroup.sub_vbo.empty())
    {
        GLuint normalVBO = bufferGroup.sub_vbo[0]; // Assume first additional VBO is normals
        glNamedBufferSubData(bufferGroup.sub_vbo[0], 0, new_normals.size() * sizeof(float) * 3, (convertToUsableFormat(new_normals)).data());
    }

    // Update Texture Coordinate
    if (!new_texcoords.empty() && bufferGroup.sub_vbo.size() > 1)
    {
        GLuint texCoordVBO = bufferGroup.sub_vbo[1]; // Assume second additional VBO is texture coordinates
        glNamedBufferSubData(GL_ARRAY_BUFFER, 0, new_texcoords.size() * sizeof(float) * 3, (convertToUsableFormat(new_texcoords)).data());
    }

    // Unbind the VAO after updates
    glBindVertexArray(0);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error during one buffer update: " << error << std::endl;
    }
}

void BufferIDsGroups::addVBO(GLuint new_vbo)
{
    this->sub_vbo.push_back(new_vbo);
}

GLuint createFBO(TextureResource &texress)
{

    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error after FBO Generations: " << error << std::endl;
        return 0;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error after glBindFramebuffer: " << error << std::endl;
        return 0;
    }
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texress.texture_id, 0);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        switch (status)
        {
        case GL_FRAMEBUFFER_UNDEFINED:
            std::cerr << "Framebuffer undefined" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            std::cerr << "Framebuffer incomplete attachment" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            std::cerr << "Framebuffer incomplete  missing attachment" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            std::cerr << "Framebuffer incomplete draw buffer" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            std::cerr << "Framebuffer incomplete read buffer" << std::endl;
            break;
        default:
            std::cerr << "Unknown framebuffer error. Status code: " << status << std::endl;
            break;
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return fbo;
}

void useFbo(GLuint fbo)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void attachFbo(GLuint fbo, TextureResource &texress)
{

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texress.texture_id, 0);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        switch (status)
        {
        case GL_FRAMEBUFFER_UNDEFINED:
            std::cerr << "Framebuffer undefined" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            std::cerr << "Framebuffer incomplete attachment" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            std::cerr << "Framebuffer incomplete  missing attachment" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            std::cerr << "Framebuffer incomplete draw buffer" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            std::cerr << "Framebuffer incomplete read buffer" << std::endl;
            break;
        default:
            std::cerr << "Unknown framebuffer error. Status code: " << status << std::endl;
            break;
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void freeBuffers(BufferIDsGroups &bufferid)
{
    // Not default Buffer
    GLuint &vao = bufferid.m_vao_id;
    GLuint &vbo = bufferid.m_vbo_id;
    GLuint &ebo = bufferid.m_ebo_id;

    if (!(vao <= 0))
    {
        // Simply add Exception here
        bufferid.zeros();
        return;
    }

    // Unbind the buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);         // Unbind VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind EBO

    // Delete the buffers
    glDeleteBuffers(1, &vbo); // Delete VBO
    glDeleteBuffers(1, &ebo); // Delete EBO
    for (auto &vbos : bufferid.sub_vbo)
    {
        glDeleteBuffers(1, &vbos); // Delete Remaining VBO if necessary
    }

    // Finally we can delete the Vao
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);

    bufferid.zeros();

    return;
}
