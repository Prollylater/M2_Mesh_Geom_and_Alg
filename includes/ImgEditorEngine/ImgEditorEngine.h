#ifndef EDITOR_H
#define EDITOR_H
#include "input.h"
// Delaunay Mesh specific treatment
#include "Mesh_IO.h"
#include "MeshHelper.h"
// Engines

#include <vector>
#include <iostream>

#include "glcore.h"
#include "Buffers.h"
#include "Program.h"
#include "Texture.h"

#include "Canvas.h"

// TODO This might be in need of a lot of refactoring

class OpenGLEngine;

namespace appobj
{
    extern OpenGLEngine glengine;
    extern Mesh meshobject; 
}

class OpenGLEngine
{

private:
    // Store Loaded vao
    BufferIDsGroups loadedvao;
    BufferIDsGroups meshvao;

    TextureResource meshtexture;

    // Store Loaded texture
    TextureResource imageress;
    // FBO
    GLuint fbo;
    // TextureResource copytext;
    // Store main Shader
    Program prog;

    CameraController controller;
    //Camera camera_obj;

public:
    OpenGLEngine();

    // TODO remove remnant of singleton patter here

    OpenGLEngine(const OpenGLEngine &) = delete;
    OpenGLEngine &operator=(const OpenGLEngine &) = delete;
    void copyTextureToFBO(GLuint &fbo, int width, int height);
    bool initImrender();
    bool initImrender(const GLFWwindow* window, const int& width,const int& height);

    bool outputImg(const char *datapath, GLuint *out_texture, int *out_width, int *out_height);
    bool loadMesh(const char *datapath, GLuint *out_texture, int *out_width, int *out_height, bool include_faces = 0, int triangulation_mode = 0);
    void renderMesh(const int &width, const int &height, const int &display_mode, const bool &display3D, const float &cam_x,
                    const float &cam_y, const float &cam_z, const float &scale);
    void updateMesh(bool indices, bool normals, bool new_texcoords, bool display3D);
    void updateTerrainto3D();
    void updateTerrainto2D();

    bool deleteTexture(GLuint &tex);
    bool saveTextInst(GLuint &out_texture, const char *filename);

};

#endif