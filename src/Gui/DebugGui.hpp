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
    const ImVec4& GetClearColor() { return m_ClearColor; }

private:
    const unsigned char* m_Vendor{ nullptr };
    const unsigned char* m_Renderer{ nullptr };
    const unsigned char* m_Version{ nullptr };

    ImGuiIO& m_IO;
    
    ImVec4 m_ClearColor{ ImVec4(0.2f, 0.5f, 0.7f, 1.0f) };
};
