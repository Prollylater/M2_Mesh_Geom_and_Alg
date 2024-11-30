#ifndef CAMERA_H
#define CAMERA_H

#include "Mat.h"
class Camera
{
public:
    Vec<float> m_origin;

    // Useful data
    float m_fov;
    float m_width;
    float m_height;
    float z_near;
    float z_far;

    // Movement
    float yaw;
    float pitch;
    float roll;
    float mvt_speed;

    Camera()
        : m_origin(),
          m_fov(45.0f),
          m_width(1080.0f),
          m_height(720.0f),
          z_near(0.1f),
          z_far(1000.0f),
          yaw(0.0f),
          pitch(0.0f),
          roll(0.0f),
          mvt_speed(0.5f) {};

    Camera(const Vec<float> &origin,
           const float &width,
           const float &height)
        : m_origin(origin),
          m_fov(45.0f),
          m_width(width),
          m_height(height),
          z_near(0.1f),
          z_far(1000.0f),
          yaw(0.0f),
          pitch(0.0f),
          roll(0.0f),
          mvt_speed(0.5f) {};

    ~Camera() = default;
    /*
    void handleKeyInput(GLFWwindow *window, float delta)
    {
        float velocity = mvt_speed * delta;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            m_origin.z += 1.0f * velocity;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            m_origin.z -= 1.0f * velocity;

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            m_origin.y += 1.0f * velocity;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            m_origin.y -= 1.0f * velocity;

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            m_origin.x -= 1.0f * velocity;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            m_origin.x += 1.0f * velocity;
    }*/

    void move(int axis, bool forward)
    {
        // Could eventually move using the Front Vector
        std::cout << "In move " << m_origin << std::endl;

        if (forward)
        {
            m_origin[axis] += 1.0f * mvt_speed;
            std::cout << "Pos after move " << m_origin << std::endl;
        }
        else
        {
            m_origin[axis] -= 1.0f * mvt_speed;
            std::cout << "Pos after move " << m_origin << std::endl;
        }
    }

    void updateMvmtSpeed(bool increase, float value = 1.0f)
    {
        std::cout << "Update speed of " << value << std::endl;
        if (increase)
        {
            mvt_speed += value;
        }
        else
        {
            mvt_speed -= value;
        }
        mvt_speed = (mvt_speed < 0) ? 1 : mvt_speed;

        std::cout << "To " << value << std::endl;
    }

    void rotate(int axis, bool forward)
    {
        int val = (-2 * forward) + 1;
        switch (axis)
        {
        case 0:
            roll += 1.0f * mvt_speed * val;
            break;
        case 1:
            yaw += 1.0f * mvt_speed * val;
            break;
        case 2:
            pitch += 1.0f * mvt_speed * val;
            break;
        default:
            break;
        }
    }

    void setPos(const Vec<float> &new_pos)
    {
        m_origin = new_pos;
    };

    Mat<float> lookat(Vec<float> target, Vec<float> up) const
    {
        return Transform::LookAt(m_origin, target, up);
    }
    Mat<float> view(bool style = 1) const
    {
        std::cout << "Pitch:" << pitch;
        std::cout << " Yaw:" << yaw;
        std::cout << " Roll:" << roll << std::endl;
        std::cout << "Pos " << m_origin << std::endl;
           
        if (style)
        {
            return Transform::RotationX(pitch) *
                   Transform::RotationZ(yaw) *
                   Transform::RotationY(roll) * Transform::Translation(m_origin.x, m_origin.y, m_origin.z);
        }
        else
        {
            return Transform::Translation(m_origin.x, m_origin.y, m_origin.z);
        }
    };

    Mat<float> projection(bool style = 1) const
    {
        if (style)
        {
            return Transform::Perspective(m_fov, m_width / m_height, z_near, z_far);
        }
        else
        {
            return Transform::Ortho(0.0f, m_width, 0.0f, m_height, -1.0f, 1.0f);
        }
    };
};

#endif