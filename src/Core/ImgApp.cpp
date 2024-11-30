#include "ImgApp.h"

ImgApp::ImgApp() : main_window()
{
  int width, height;
  if (!OpenGlContext::initGlContext(main_window, 1024, 576))
  {
    std::cerr << "OpenGLContext initialization failed" << std::endl;
  }

  bool eval = ImGuiAppContext::init(main_window);

  if (!eval)
  {
    std::cerr << "ImGuiAppContext initialization failed" << std::endl;
  }

  glfwGetWindowSize(main_window, & width, &height);

  if (!appobj::glengine.initImrender(main_window,width,height ))
  {
    std::cerr << "Buffers Initialization failed" << std::endl;
  }
}

void ImgApp::start()
{
  while (!glfwWindowShouldClose(main_window))
  {
    // Render

    OpenGlContext::preRender();

    ImGuiAppContext::preRender();
  
    ImGuiAppContext::Render();

    OpenGlContext::postRender(main_window);

    ImGuiAppContext::postRender();
  }
}
void ImgApp::quit()
{

  // Liberate necessary ressource
  ImGuiAppContext::quit();

  OpenGlContext::quit(main_window);
}
