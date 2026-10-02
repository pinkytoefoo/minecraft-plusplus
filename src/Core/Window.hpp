#pragma once

#include <cstdint>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Event.hpp"
#include "Util/SPSCQueue.hpp"

class Window
{
public:
    Window(int width, int height, const std::string& title /* must be null terminated*/);
    ~Window();
    Window(const Window&) = delete;
    void operator=(const Window&) = delete;
    Window(Window&&) = delete;
    void operator=(Window&&) = delete;

    bool PollEvent(Event& outEvent)
    {
        return m_Queue.Pop(outEvent);
    }
    
    bool IsRunning() const { return !glfwWindowShouldClose(m_Handle); }
    void SwapBuffers() const { glfwSwapBuffers(m_Handle); }
    
    GLFWwindow* NativeHandle() const { return m_Handle; }
    int GetWidth() const { return m_Data.Width; }
    int GetHeight() const { return m_Data.Height; }

private:
    using EventQueue = SPSCQueue<Event, 128>;
    EventQueue m_Queue;

    GLFWwindow* m_Handle{nullptr};
    struct WindowData
    {
        WindowData(int width, int height)
            : Width{width}, Height{height}
        {
        }
        int Width, Height;
        bool IsMouseCaptured{false};
    };
    WindowData m_Data;
};
