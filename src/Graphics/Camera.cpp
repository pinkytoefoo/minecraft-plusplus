#include <cmath>

#include "Camera.hpp"

Camera::Camera(float ratio, float fov, float near_clip, float far_clip)
    : m_FOV{fov}
    , m_AspectRatio{ratio}
    , m_Near{near_clip}
    , m_Far{far_clip}
{
    // UpdateView();
    // UpdateProjection();
}


void Camera::ProcessKeyboard(CameraDirection direction, float deltaTime) {
    const float cameraSpeed = 10.0f * deltaTime;

    glm::vec3 right = glm::normalize(glm::cross(m_Front, m_Up));
    glm::vec3 velocity = glm::vec3(0.0f);

    velocity += m_Front * static_cast<float>(direction & CameraDirection::Forward);
    velocity -= m_Front * static_cast<float>(direction & CameraDirection::Backward);
    velocity += right   * static_cast<float>(direction & CameraDirection::Right);
    velocity -= right   * static_cast<float>(direction & CameraDirection::Left);
    velocity += m_Up    * static_cast<float>(direction & CameraDirection::Up);
    velocity -= m_Up    * static_cast<float>(direction & CameraDirection::Down);

    m_Position += velocity * cameraSpeed;
}

void Camera::ProcessMouse(double xpos, double ypos)
{
    double xOffset = xpos - m_LastMouseX;
    double yOffset = m_LastMouseY - ypos;

    m_LastMouseX = xpos;
    m_LastMouseY = ypos;

    xOffset *= m_MouseSensitivity;
    yOffset *= m_MouseSensitivity;

    m_Yaw += static_cast<float>(xOffset);
    m_Pitch += static_cast<float>(yOffset);

    m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);

    glm::vec3 direction{
        std::cos(glm::radians(m_Yaw)) * std::cos(glm::radians(m_Pitch)), // x
        std::sin(glm::radians(m_Pitch)),                                 // y
        std::sin(glm::radians(m_Yaw)) * std::cos(glm::radians(m_Pitch)), // z
    };

    m_Front = glm::normalize(direction);
}
