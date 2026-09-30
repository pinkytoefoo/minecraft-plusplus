#include <functional>
#include <stdexcept>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <stb_image.h>

#include "Window.hpp"
#include "Util.hpp"

#ifdef _WIN32
#   define GLFW_EXPOSE_NATIVE_WIN32
#   include <GLFW/glfw3native.h>
#   include <dwmapi.h>

#   ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#       define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#   endif
#endif

Window::Window(int width, int height, const std::string& title)
    : m_Data{width, height}
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_WIN32_KEYBOARD_MENU, GLFW_TRUE);
    // glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    // glfwWindowHint(GLFW_SAMPLES, 8);

    m_Handle = glfwCreateWindow(m_Data.Width, m_Data.Height, title.data(), nullptr, nullptr);

    if(!m_Handle)
    {
       throw std::runtime_error{"glfwCreateWindow() failed"};
    }

    glfwGetFramebufferSize(m_Handle, &m_Data.Width, &m_Data.Height);

    glfwMakeContextCurrent(m_Handle);
    ASSERT_INIT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
    glViewport(0, 0, m_Data.Width, m_Data.Height);

    GLFWimage images[1];
    images[0].pixels = stbi_load("assets/textures/dirt.png", &images[0].width, &images[0].height, 0, 4);
    if (images[0].pixels) {
        glfwSetWindowIcon(m_Handle, 1, images);
        stbi_image_free(images[0].pixels);
    }

    // setting window to dark mode
    #ifdef _WIN32
    HWND hwnd = glfwGetWin32Window(m_Handle);
    BOOL value = TRUE;
    DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &value, sizeof(value));
    #endif

    glfwSetWindowUserPointer(m_Handle, this);
    glfwSetFramebufferSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height) {
        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        self->m_Data.Width = width;
        self->m_Data.Height = height;

        glViewport(0, 0, self->m_Data.Width, self->m_Data.Height);

        self->m_Queue.Push(Event{WindowResizeEvent{width, height}});
    });

    glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if(action != GLFW_PRESS)
            return;
        
        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        switch(key)
        {
            case GLFW_KEY_F11:
                (!glfwGetWindowAttrib(window, GLFW_MAXIMIZED)) ? glfwMaximizeWindow(window) : glfwRestoreWindow(window);
                break;
        }
        self->m_Queue.Push(Event{ KeyEvent{ key, scancode, action, mods } });
    });
}

Window::~Window()
{
    glfwDestroyWindow(m_Handle);
}
