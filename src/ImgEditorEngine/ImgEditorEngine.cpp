#include "ImgEditorEngine.h"
#define GET_NUM_CHANNELS(internalFormat)                             \
    (internalFormat) == GL_RED ? 1 : (internalFormat) == GL_RG   ? 2 \
                                 : ((internalFormat) == GL_RGB)  ? 3 \
                                 : ((internalFormat) == GL_RGBA) ? 4 \
                                                                 : 0

// Define instance of the app object which each correspond to a feature
namespace appobj
{
    // Opengl Engine declared elsewhere
    OpenGLEngine glengine;
    Mesh meshobject; // here

    // TODO: Move it
    std::vector<Vertices> curr_mesh_bound; // Reposition
    float mesh_scaling;                    // Uppers caling

}

OpenGLEngine::OpenGLEngine() //: activevao(0), activetexture(0)
{

};

bool OpenGLEngine::initImrender()
{
    // Initialize the Vao allowing to render the image as a texture
    // This vao is always a plane taking a Mat<uint8> data as texture.
    // Create an unique fbo and it's designated rendering texture
    std::vector<Vec<float>> canvas = {
        Vec(-1.0f, -1.0f, 0.0f),
        Vec(-1.0f, 1.0f, 0.0f),
        Vec(1.0f, 1.0f, 0.0f),
        Vec(1.0f, -1.0f, 0.0f)};

    std::vector<Vec<float>> canvastext = {
        Vec(0.0f, 0.0f, 0.0f),
        Vec(0.0f, 1.0f, 0.0f),
        Vec(1.0f, 1.0f, 0.0f),
        Vec(1.0f, 0.0f, 0.0f)

    };

    std::vector<GLuint> indices = {0, 1, 2, 2, 3, 0};

    loadedvao = createBuffers(canvas, indices, canvastext);
    // TODO Array of shader for each change
    // Init program with the generic loading shader
    prog.init("./ressources/shaders/meshshade.vs", "./ressources/shaders/meshshade.fs");

    return true;
}

// TODO better management of canvas and current state to avoid this treatment
// Save an image
// Invoked when the image wasn't already stored in a canvas
// Result of operation etc..
bool OpenGLEngine::saveTextInst(GLuint &out_texture, const char *filename)
{
    GLint width, height, format;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, out_texture);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &format);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    int channels = GET_NUM_CHANNELS(format);
    // TODO Channles data not stored
    int size = width * height * (channels);
    if (channels == 3)
    {
        // Use Pack Alignment to mirror the UNPACK_ALIGNMENT at write
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
    }

    std::cout << "Size related to file writing (w, h, chan): " << std::endl;
    std::cout << width << " " << height << channels << std::endl;
    uint8_t *pixels = new uint8_t[size];

    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error during saving  imagefrom texture " << error << std::endl;
        return 0;
    }
    // TODO GIve choice between mutiple format
    writeImgJpg(filename, pixels, width, height, channels, true);
}

// TOODO change names of the "output" functions
// Layer choice
// Handling current vector states
// Lot of thing to modify

bool OpenGLEngine::loadMesh(const char *datapath, GLuint *out_texture, int *out_width, int *out_height, bool include_faces, int triangulation)
{
    std::cout << "Loding mesh at: " << datapath << std::endl;
    Mat<uint8_t> tmpmat(*out_height, *out_width, 3, PixlColorSpace::BGR);
    if (include_faces)
    {
        appobj::meshobject = load_mesh(datapath);
    }
    else
    {
        // 0 would remove the z coordinate
        appobj::meshobject = load_mesh_faceless(datapath, 1);
    }
    if (appobj::meshobject.getVerticesNb() <= 0)
    {
        return false;
    }
    if (!include_faces)
    {
        std::cout << "Triangulation with algo " << triangulation << std::endl;
        switch (triangulation)
        {
        case 0:
            appobj::meshobject.incremental_triangulate2(); // TODO::
            break;
        case 1:
            appobj::meshobject.incremental_triangulate(); // TODO::
            break;
        case 2:
            // Bowyerwatson
            break;
        default:
            break;
        }
    }
    std::cout << "Triangulation done " << std::endl;

    // Second texture may have no purpose out in the current build
    std::cout << "Texture Creation " << tmpmat.getChannels() << std::endl;
    
    initTextRess(imageress, makeTextureMat(0, tmpmat));
    int chan= 3;
     Mat<uint8_t> tmptex;
    
    initTextRess(meshtexture,read_texture(0,"./ressources/texture/hsv_palette.png",tmptex, chan));
    // TODO Canvas set up Should not be handled here

    if (fbo == 0)
    { // Create a fbo for other renderings
        std::cout << "Creating Fbo " << tmpmat.getChannels() << std::endl;
        fbo = createFBO(imageress);
    }
    std::cout << "Display texture made" << std::endl;

    std::vector<Vertices> normals = appobj::meshobject.compute_mesh_normal();
    std::vector<Vertices> curvature = appobj::meshobject.compute_mean_curvature_tex_coords();
    std::vector<Vertices> positions = appobj::meshobject.getVerticeArray();

    // Bound as a sphere
    appobj::curr_mesh_bound = appobj::meshobject.getBounds();
    Vertices size = appobj::curr_mesh_bound[0] - appobj::curr_mesh_bound[1];
    float largest_axis = std::max(size.x, std::max(size.y, size.z));
    appobj::mesh_scaling = 1000.0f / largest_axis;

    meshvao = createBuffers(positions, appobj::meshobject.getFacesArray(), normals,
                            curvature);

    // Texture that will be displayed
    *out_texture = imageress.texture_id;

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error durings engine texture loading function: " << error << std::endl;
    }
    return 1;
}

bool OpenGLEngine::deleteTexture(GLuint &tex)
{
    glBindTexture(GL_TEXTURE_2D, 0);
    freeTexture(tex);
}

void OpenGLEngine::copyTextureToFBO(GLuint &tex, int width, int height)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set viewport to correct size

    glViewport(0, 0, width, height);

    prog.reset();
    prog.init("./ressources/shaders/.vs", "./ressources/shaders/imgoutput.fs");

    prog.use();
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    GLenum fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "Framebuffer not complete: " << fboStatus << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return;
    }
    glBindVertexArray(loadedvao.getVao());

    // Create a temporary Ressource holder
    TextureResource temp_tex_res;
    initTextRess(temp_tex_res, tex);

    bindTexture(temp_tex_res, prog.shader_id, "image_color");
    std::cout << "id" << prog.shader_id << std::endl;
    glDrawElements(GL_TRIANGLE_STRIP, loadedvao.m_count, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error durings engine update texture function: " << error << std::endl;
    }
}

// Only call for the first renderPass
void OpenGLEngine::renderMesh(const int &width, const int &height, const int &display_mode, const bool &display3D, const float &cam_x,
                              const float &cam_y, const float &cam_z, const float &scale)
{
    GLenum error;

    // Display mode 1 Wireframe, 2 Normals recalcualted with Laplacian, 3 Curvature
    if (display_mode != 1)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    // Set viewport to correct size
    prog.use();
    Mat<float> model = Transform::Scale(scale, scale,scale) * Transform::Identity();
    // Mat<float> projection = Transform::Perspective(50, width / height, 0.01, 1000);
    Mat<float> projection = Transform::Ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
    // We're specifically working with this view matrix in 2d
    // Mat<float> view = Transform::LookAt(Vec<float>(cam_x, cam_y, cam_z), Vec<float>(0, 0, 0), Vec<float>(0, 1.0, 0.0));
    Mat<float> view = Transform::Translation(cam_x, cam_y, cam_z);

    Mat<float> mv = view * model;
    Mat<float> mvp = projection * mv;

    //prog.addUniform4("modelMatrix", model);
    //prog.addUniform4("viewMatrix", view);
    //prog.addUniform4("projectionMatrix", projection);

    //prog.addUniform4("mvMatrix", mvp);
    prog.addUniform4("mvpMatrix", mvp);
    //prog.addUniform1("DisplayMode", display_mode);
    //prog.addUniform1("3dmode", display3D);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLenum fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "Framebuffer not complete: " << fboStatus << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return;
    }

    glBindVertexArray(meshvao.getVao());
    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error post fbo: " << error << std::endl
                  << std::endl;
    }

     bindTexture(meshtexture, prog.shader_id, "mesh_color");

    // Directly use the size of the to color arrray sinnce no ebo were crearted for this
    // TODO create draw function that cna make this choice
    int indices_count = appobj::meshobject.getFacesNb() * 3;

    glDrawElements(GL_TRIANGLES, meshvao.getCount(), GL_UNSIGNED_INT, nullptr); // Draw 1 point

    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error post draw: " << error << std::endl
                  << std::endl;
    }
    glBindVertexArray(0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // saveTextInst(imageress.texture_id, "Test.jpg");
    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error during rerender function: " << error << std::endl
                  << std::endl;
    }
}

void OpenGLEngine::updateMesh(bool indices, bool normals, bool new_texcoords, bool display3D)
{
    // ALways and Vertices
    if (display3D)
    {
        std::cout<<"Update to 3d"<<std::endl;

        updateTerrainto3D();
    }
    else
    {
        updateTerrainto2D();
    }
    /*
    if (indices)
    {
        updateBuffer(meshvao, {}, appobj::meshobject.getFacesArray());
    }

    if (normals)
    {
        updateBuffer(meshvao, {}, {}, appobj::meshobject.compute_mesh_normal(), {});
    }
    if (new_texcoords)
    {
        updateBuffer(meshvao, {}, {}, {}, appobj::meshobject.compute_mean_curvature_tex_coords());
    }
    */
}

void OpenGLEngine::updateTerrainto3D()
{
    updateBuffer(meshvao, appobj::meshobject.getVerticeArray());
};
void OpenGLEngine::updateTerrainto2D()
{
    std::vector<Vertices> flat_position;
    for (size_t i = 0; i < appobj::meshobject.getVerticesNb(); i++)
    {
        flat_position.emplace_back(appobj::meshobject.getVertice(i).x, appobj::meshobject.getVertice(i).y, 0.0);
    }
    updateBuffer(meshvao, flat_position);
};
