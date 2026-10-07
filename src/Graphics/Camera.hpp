#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>

enum class CameraDirection : uint8_t {
    None      = 0,
    Forward   = 1 << 0,
    Backward  = 1 << 1,
    Left      = 1 << 2,
    Right     = 1 << 3,
    Up        = 1 << 4,
    Down      = 1 << 5,
};

inline CameraDirection operator|(CameraDirection lhs, CameraDirection rhs) {
    return static_cast<CameraDirection>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

inline bool operator&(CameraDirection lhs, CameraDirection rhs) {
    return (static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs)) != 0;
}

inline CameraDirection& operator|=(CameraDirection& lhs, CameraDirection rhs) {
    lhs = lhs | rhs;
    return lhs;
}

class Camera
{
public:
    Camera(float ratio, float fov = 90.0f, float near_clip = 0.01f, float far_clip = 100.0f);

    void SetAspectRatio(float ratio) { m_AspectRatio = ratio; }
    void Move(const glm::vec3& offset);

    void ProcessKeyboard(CameraDirection direction, float deltaTime);
    void ProcessMouse(double xpos, double ypos);

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

    float m_Yaw{-90.0f};
    float m_Pitch{0.0f};

    double m_LastMouseX{0.0};
    double m_LastMouseY{0.0};

    float m_MouseSensitivity{0.1f};

    float m_FOV, m_AspectRatio, m_Near, m_Far;
};