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

    void setAspectRatio(float ratio) { aspectRatio_ = ratio; }
    void move(const glm::vec3& offset);

    void processKeyboard(CameraDirection direction, float deltaTime);
    void processMouse(double xpos, double ypos);

    void rotate();

    inline const glm::mat4 getViewMatrix() const { return glm::lookAt(position_, position_ + front_, up_); }
    inline const glm::mat4 getProjectionMatrix() const { return glm::perspective(glm::radians(fov_), aspectRatio_, near_, far_); }

    const glm::vec3& getPosition() const { return position_; }

private:
    void updateView();
    void updateProjection();
    glm::vec3 position_{glm::vec3(0.0f, 0.0f,  3.0f)};
    glm::vec3 front_{glm::vec3(0.0f, 0.0f, -1.0f)};
    glm::vec3 up_{glm::vec3(0.0f, 1.0f,  0.0f)};

    float yaw_{-90.0f};
    float pitch_{0.0f};

    double lastMouseX_{0.0};
    double lastMouseY_{0.0};

    float mouseSensitivity_{0.1f};

    float fov_, aspectRatio_, near_, far_;
};
