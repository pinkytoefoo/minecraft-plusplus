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


void Camera::ProcessKeyboard(CameraDirection direction, float deltaTime)
{
    const float cameraSpeed = 10.0f * deltaTime;

    switch(direction)
    {
        case CameraDirection::FORWARD:
            m_Position += cameraSpeed * m_Front;
            break;
        case CameraDirection::BACKWARD:
            m_Position -= cameraSpeed * m_Front;
            break;
        case CameraDirection::LEFT:
            m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * cameraSpeed;
            break;
        case CameraDirection::RIGHT:
            m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * cameraSpeed;
            break;
    }
}

void Camera::ProcessMouse()
{

}
