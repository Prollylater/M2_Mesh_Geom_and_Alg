
#ifndef INPUT_H
#define INPUT_H
#include "camera.h"
#include <memory>

class InputHandler
{
protected:
    bool rotationdir = 1;

public:
    virtual ~InputHandler() = default;

    // Handle a Camera input
    virtual void handleMovementInput(Camera &camera, float deltaTime) = 0;
    virtual void handleRotationInput(Camera &camera, float deltaTime) = 0;
};

#ifdef GLFW_APP
#include <GLFW/glfw3.h>

class GLFWInputHandler : public InputHandler
{
public:
    GLFWInputHandler(GLFWwindow *window) : m_Window(window) {}

    void handleMovementInput(Camera &camera, float deltaTime) override
    {
        float speed = 2.5f * deltaTime;
        float velocity = mvt_speed * delta;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camera.move(2, 1);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            camera.move(2, 0);
        }

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            camera.move(1, 1);
        }
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        {
            camera.move(1, 0);
        }

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            camera.move(0, 1);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            camera.move(0, 0);
        }
    }
    void handleRotationInput(Camera &camera, float deltaTime) override
    {
        // Not yet Mouse Input
        // TODO: Handle Rotation Here
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        {
            rotationdir = !rotationdir;
        }
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        {
            camera.rotate(rotationdir);
        }
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        {
            camera.rotate(rotationdir);
        }
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        {
            camera.rotate(rotationdir);
        }
    }

private:
    GLFWwindow *m_Window;
};
#endif


#define IMGUI_APP
#ifdef IMGUI_APP

#include <imgui.h>

class ImGuiInputHandlerC : public InputHandler
{
public:
    void handleMovementInput(Camera &camera, float deltaTime) override
    {
        float speed = 2.5f * deltaTime;
        if (ImGui::IsKeyDown(ImGuiKey_R))
        {
            camera.updateMvmtSpeed(1,0.05);
        }
        if (ImGui::IsKeyDown(ImGuiKey_F))
        {
            camera.updateMvmtSpeed(0,0.05);
        }
        if (ImGui::IsKeyDown(ImGuiKey_Z))
        {
            std::cout<<"U clicked" <<std::endl;

            camera.move(2, 1);
        }
        if (ImGui::IsKeyDown(ImGuiKey_S))
        {
            std::cout<<"U clicked" <<std::endl;

            camera.move(2, 0);
        }
        if (ImGui::IsKeyDown(ImGuiKey_Q))
        {
            std::cout<<"U clicked" <<std::endl;

            camera.move(0, 1);
        }
        if (ImGui::IsKeyDown(ImGuiKey_D))
        {
            std::cout<<"U clicked" <<std::endl;

            camera.move(0, 0);
        }
        if (ImGui::IsKeyDown(ImGuiKey_A))
        {
            camera.move(1, 1);
        }
        if (ImGui::IsKeyDown(ImGuiKey_E))
        {
            
            camera.move(1, 0);
        }
    }
    void handleRotationInput(Camera &camera, float deltaTime) override
    {
        if (ImGui::IsKeyDown(ImGuiKey_U))
        {
            rotationdir = !rotationdir;
        }
        if (ImGui::IsKeyDown(ImGuiKey_I))
        {
            camera.rotate(0,rotationdir);
        }
        if (ImGui::IsKeyDown(ImGuiKey_O))
        {
            camera.rotate(1, rotationdir);
        }
        if (ImGui::IsKeyDown(ImGuiKey_P))
        {
            camera.rotate(2,rotationdir);
        }
    }
};
#endif


class CameraController
{
public:
    CameraController() = default;
    CameraController(std::shared_ptr<Camera> camera, std::shared_ptr<InputHandler> inputHandler)
        : m_Camera(camera), m_InputHandler(inputHandler) {}

    void setInputHandler(std::shared_ptr<InputHandler> inputHandler)
    {
        m_InputHandler = inputHandler;
    }

    void update(float deltaTime)
    {
        if (m_InputHandler){
            m_InputHandler->handleMovementInput(*m_Camera, deltaTime);
            m_InputHandler->handleRotationInput(*m_Camera, deltaTime);
        }
    }

    std::shared_ptr<Camera> GetCamera() const { return m_Camera; }
    std::shared_ptr<InputHandler> GetInputHandler()  { return m_InputHandler; }


private:
    std::shared_ptr<Camera> m_Camera;
    std::shared_ptr<InputHandler> m_InputHandler;
};

#endif