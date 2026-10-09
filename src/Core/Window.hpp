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
    Window(int width, int height, const std::string& title /* must be null terminated, so use str ref instead of view */);
    ~Window();
    Window(const Window&) = delete;
    void operator=(const Window&) = delete;
    Window(Window&&) = delete;
    void operator=(Window&&) = delete;

    bool getEventFromQueue(Event& outEvent)
    {
        return queue_.pop(outEvent);
    }
    
    bool isRunning() const { return !glfwWindowShouldClose(handle_); }
    inline void swapBuffers() const { glfwSwapBuffers(handle_); }
    inline void pollEvents() const { glfwPollEvents(); }
    
    GLFWwindow* nativeHandle() const { return handle_; }
    int getWidth() const { return data_.width; }
    int getHeight() const { return data_.height; }
    float getRatio() const { return static_cast<float>(data_.width) / static_cast<float>(data_.height); }

private:
    using EventQueue = SPSCQueue<Event, 128>;
    EventQueue queue_;

    GLFWwindow* handle_{nullptr};
    struct WindowData
    {
        WindowData(int w, int h)
            : width{w}, height{h}
        {
        }
        int width, height;
        bool isMouseCaptured{false};
    };
    WindowData data_;
};
