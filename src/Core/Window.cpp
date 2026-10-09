#include <stdexcept>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <stb_image.h>

#include "Window.hpp"

#ifdef _WIN32
#   define GLFW_EXPOSE_NATIVE_WIN32
#   include <GLFW/glfw3native.h>
#   include <dwmapi.h>

#   ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#       define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#   endif
#endif

Window::Window(int width, int height, const std::string& title)
    : data_{width, height}
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_WIN32_KEYBOARD_MENU, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    handle_ = glfwCreateWindow(data_.width, data_.height, title.data(), nullptr, nullptr);

    if(!handle_)
    {
       throw std::runtime_error{"glfwCreateWindow() failed"};
    }

    glfwGetFramebufferSize(handle_, &data_.width, &data_.height);

    glfwMakeContextCurrent(handle_);
    // start implementing exceptions
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glViewport(0, 0, data_.width, data_.height);

    // todo: add icons of difference sizes
    GLFWimage images[1];
    images[0].pixels = stbi_load("assets/textures/dirt.png", &images[0].width, &images[0].height, 0, 4);
    if (images[0].pixels) {
        glfwSetWindowIcon(handle_, 1, images);
        stbi_image_free(images[0].pixels);
    }

    // setting window to dark mode
    #ifdef _WIN32
    HWND hwnd = glfwGetWin32Window(handle_);
    BOOL value = TRUE;
    DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &value, sizeof(value));
    #endif

    glfwSetWindowUserPointer(handle_, this);
    glfwSetFramebufferSizeCallback(handle_, [](GLFWwindow* window, int width, int height) {
        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        self->data_.width = width;
        self->data_.height = height;

        glViewport(0, 0, self->data_.width, self->data_.height);

        self->queue_.push(Event{WindowResizeEvent{width, height}});
    });

    glfwSetKeyCallback(handle_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        switch(key)
        {
            case GLFW_KEY_F11:
                if(action != GLFW_PRESS)
                    break;
                if(!glfwGetWindowAttrib(window, GLFW_MAXIMIZED))
                    glfwMaximizeWindow(window);
                else
                    glfwRestoreWindow(window);
                break;

            case GLFW_KEY_ESCAPE:
                if(action != GLFW_PRESS)
                    break;

                if(glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                else
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                // if (glfwRawMouseMotionSupported())
                // {
                //     glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
                // }
                break;

            default:
                self->queue_.push(Event{KeyEvent{key, scancode, action, mods}});
                break;
        }
    });

    glfwSetCursorPosCallback(handle_, [](GLFWwindow* window, double xpos, double ypos) {
        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        self->queue_.push(Event{MouseMoveEvent{xpos, ypos}});
    });
}

Window::~Window()
{
    glfwDestroyWindow(handle_);
}
