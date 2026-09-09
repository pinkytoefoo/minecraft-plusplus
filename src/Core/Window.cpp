#include <iostream>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include "Window.hpp"

Window::Window(int width, int height, std::string_view title)
    : m_Data{width, height}
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_WIN32_KEYBOARD_MENU, GLFW_TRUE);
    // glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    // glfwWindowHint(GLFW_SAMPLES, 8);

    m_Handle = glfwCreateWindow(m_Data.Width, m_Data.Height, title.data(), nullptr, nullptr);

    if(!m_Handle)
    {
       throw std::runtime_error{"glfwCreateWindow() failed"};
    }

    glfwMakeContextCurrent(m_Handle);
    glfwSetWindowUserPointer(m_Handle, this);   
    glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height) {
        Window* self = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

        self->m_Data.Width = width;
        self->m_Data.Height = height;

        glViewport(0, 0, self->m_Data.Width, self->m_Data.Height);
        self->m_ResizeCallback();
    });

    glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if(scancode != GLFW_PRESS)
            return;
        
        Window* self = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

        switch(key)
        {
            case GLFW_KEY_F11:
                glfwMaximizeWindow(window);
                break;
        }
    });
}

Window::~Window()
{
    glfwDestroyWindow(m_Handle);
}

void Window::OnUpdate()
{
    glfwSwapBuffers(m_Handle);
}
