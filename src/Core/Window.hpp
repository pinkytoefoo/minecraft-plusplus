#pragma once

#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>

class Window
{
public:
    Window(int width, int height, std::string_view title);
    ~Window();

    bool Init();
    void OnUpdate();
    GLFWwindow* GetWindow() { return m_Handle; }
    int GetWidth() { return m_Width; }
    int GetHeight() { return m_Height; }
private:
    GLFWwindow* m_Handle;
    int m_Width, m_Height;
    std::string m_Title;
};