#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include "Window.hpp"

Window::Window(int width, int height, std::string_view title)
    : m_Width(width), m_Height(height), m_Title(title)
{
}

Window::~Window()
{
    glfwDestroyWindow(m_Handle);
}

bool Window::Init()
{
    if(!glfwInit())
    {
       std::cerr << "glfw failed to init\n";
       return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_WIN32_KEYBOARD_MENU, GLFW_TRUE);
    // glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    // glfwWindowHint(GLFW_SAMPLES, 8);

    m_Handle = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    if(!m_Handle)
    {
       std::cerr << "window failed to create\n";
       return false;
    }
    glfwSetWindowUserPointer(m_Handle, this);   
    glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height) {
        Window* self = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if(!self) {
            throw std::runtime_error{"failed to retrieve window on resize"};
        }
        self->m_Width = width;
        self->m_Height = height;

        glViewport(0, 0, self->m_Width, self->m_Height);
    });

    return true;
}

void Window::OnUpdate()
{
    glfwSwapBuffers(m_Handle);
}
