#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>

enum class CameraDirection : uint8_t {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera(float ratio, float fov = 90.0f, float near_clip = 0.01f, float far_clip = 100.0f);

    void SetAspectRatio(float ratio) { m_AspectRatio = ratio; }
    void Move(const glm::vec3& offset);

    void ProcessKeyboard(CameraDirection direction, float deltaTime);
    void ProcessMouse();

    void Rotate();

    inline const glm::mat4 GetViewMatrix() const { return glm::lookAt(m_Position, m_Position + m_Front, m_Up); }
    inline const glm::mat4 GetProjectionMatrix() const { return glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_Near, m_Far); }

    const glm::vec3& GetPosition() const { return m_Position; }

private:
    void UpdateView();
    void UpdateProjection();
    glm::vec3 m_Position{glm::vec3(0.0f, 0.0f,  3.0f)};
    glm::vec3 m_Front{glm::vec3(0.0f, 0.0f, -1.0f)};
    glm::vec3 m_Up{glm::vec3(0.0f, 1.0f,  0.0f)};

    float m_FOV, m_AspectRatio, m_Near, m_Far;
};