#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

class DebugGui
{
public:
    DebugGui();

    void OnUpdate();
    
    // TODO: abstract clear color into renderer
    const ImVec4& getClearColor() const { return clear_color_; }

private:
    const unsigned char* vendor_{ nullptr };
    const unsigned char* renderer_{ nullptr };
    const unsigned char* version_{ nullptr };

    ImGuiIO& io_;
    
    ImVec4 clear_color_{ ImVec4(0.2f, 0.5f, 0.7f, 1.0f) };
};
