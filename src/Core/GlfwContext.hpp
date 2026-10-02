#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Util.hpp"

struct GlfwContext
{
    GlfwContext()
    {
        ASSERT_INIT(glfwInit());
  
        glfwSetErrorCallback([](int code, const char* message) {
            std::cerr << "glfwError:\n\tcode - 0x"<< std::hex << code << "\n\tmessage: " << message << "\n";
        });
    };

    ~GlfwContext() { glfwTerminate(); }

    GlfwContext(const GlfwContext&) = delete;
    GlfwContext& operator=(const GlfwContext&) = delete;
    GlfwContext(GlfwContext&&) = delete;
    GlfwContext& operator=(GlfwContext&&) = delete;
};
