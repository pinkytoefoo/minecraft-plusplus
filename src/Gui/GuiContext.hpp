#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

struct GuiContext
{
    explicit GuiContext(GLFWwindow* window);
    ~GuiContext();

    GuiContext(const GuiContext&) = delete;
    void operator=(const GuiContext&) = delete;
    GuiContext(GuiContext&&) = delete;
    void operator=(GuiContext&&) = delete;

    void StartFrame();
    
    void EndFrame();
};
