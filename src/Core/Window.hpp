#pragma once

#include <functional>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window(int width, int height, const std::string& title /* must be null terminated*/);
    ~Window();
    Window(const Window&) = delete;
    void operator=(const Window&) = delete;
    Window(Window&&) = delete;
    void operator=(Window&&) = delete;

    void SetFramebufferCallback(std::function<void(int width, int height)> callback)
    {
        m_FramebufferCallback = std::move(callback);
    }

    GLFWwindow* GetWindow() const { return m_Handle; }
    int GetWidth() const { return m_Data.Width; }
    int GetHeight() const { return m_Data.Height; }
private:
    std::function<void(int width, int height)> m_FramebufferCallback;

    GLFWwindow* m_Handle{nullptr};
    struct WindowData
    {
        WindowData(int width, int height)
            : Width{width}, Height{height}
        {
        }
        int Width, Height;
    };
    WindowData m_Data;
};
