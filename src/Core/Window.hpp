#pragma once

#include <functional>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window(int width, int height, std::string_view title);
    ~Window();

    void SetResizeCallback(std::function<void(void)>&& callback)
    {
        m_ResizeCallback = std::forward<std::function<void(void)>>(callback);
    }

    void OnUpdate();
    GLFWwindow* GetWindow() const { return m_Handle; }
    int GetWidth() const { return m_Data.Width; }
    int GetHeight() const { return m_Data.Height; }
private:
    struct WindowData
    {
        WindowData() = default;
        WindowData(int width, int height)
            : Width{width}, Height{height}
            , Maximized{false}
        {
        }
        int Width{1024}, Height{1024};
        bool Maximized{false};
    };
    WindowData m_Data;
    GLFWwindow* m_Handle{nullptr};
    std::function<void(void)> m_ResizeCallback;
};
