#include <cmath>

#include "Camera.hpp"

Camera::Camera(float ratio, float fov, float near_clip, float far_clip)
    : fov_{fov}
    , aspectRatio_{ratio}
    , near_{near_clip}
    , far_{far_clip}
{
    // UpdateView();
    // UpdateProjection();
}


void Camera::processKeyboard(CameraDirection direction, float deltaTime) {
    const float cameraSpeed = 10.0f * deltaTime;

    glm::vec3 right = glm::normalize(glm::cross(front_, up_));
    glm::vec3 velocity = glm::vec3(0.0f);

    velocity += front_ * static_cast<float>(direction & CameraDirection::Forward);
    velocity -= front_ * static_cast<float>(direction & CameraDirection::Backward);
    velocity += right   * static_cast<float>(direction & CameraDirection::Right);
    velocity -= right   * static_cast<float>(direction & CameraDirection::Left);
    velocity += up_    * static_cast<float>(direction & CameraDirection::Up);
    velocity -= up_    * static_cast<float>(direction & CameraDirection::Down);

    position_ += velocity * cameraSpeed;
}

void Camera::processMouse(double xpos, double ypos)
{
    double xOffset = xpos - lastMouseX_;
    double yOffset = lastMouseY_ - ypos;

    lastMouseX_ = xpos;
    lastMouseY_ = ypos;

    xOffset *= mouseSensitivity_;
    yOffset *= mouseSensitivity_;

    yaw_ += static_cast<float>(xOffset);
    pitch_ += static_cast<float>(yOffset);

    pitch_ = glm::clamp(pitch_, -89.0f, 89.0f);

    glm::vec3 direction{
        std::cos(glm::radians(yaw_)) * std::cos(glm::radians(pitch_)), // x
        std::sin(glm::radians(pitch_)),                                // y
        std::sin(glm::radians(yaw_)) * std::cos(glm::radians(pitch_)), // z
    };

    front_ = glm::normalize(direction);
}
