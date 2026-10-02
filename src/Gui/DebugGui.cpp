#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>

#include "DebugGui.hpp"

DebugGui::DebugGui()
    : m_IO{ImGui::GetIO()}
    , m_ClearColor{ImVec4(0.2f, 0.5f, 0.7f, 1.0f)}
{
    m_Vendor   = glGetString(GL_VENDOR);
    m_Renderer = glGetString(GL_RENDERER);
    m_Version  = glGetString(GL_VERSION);
}

void DebugGui::OnUpdate()
{
    ImGui::Begin("Configurer");
    ImGui::ColorEdit3("clear color", (float*)&m_ClearColor);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / m_IO.Framerate, m_IO.Framerate);
    ImGui::Spacing();

    if (ImGui::CollapsingHeader("System Diagnostics"))
    {
        ImGui::Spacing();
        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(12.0f, 4.0f));

        if (ImGui::BeginTable("SystemInfoTable", 2)) 
        {
            ImGui::TableSetupColumn("Key", ImGuiTableColumnFlags_WidthFixed, 100.0f);
            ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthStretch);

            ImGui::TableNextRow();
            ImGui::TableNextColumn(); ImGui::Text("Vendor:");
            ImGui::TableNextColumn(); ImGui::Text("%s", m_Vendor);

            ImGui::TableNextRow();
            ImGui::TableNextColumn(); ImGui::Text("Renderer:");
            ImGui::TableNextColumn(); ImGui::Text("%s", m_Renderer);

            ImGui::TableNextRow();
            ImGui::TableNextColumn(); ImGui::Separator();
            ImGui::TableNextColumn(); ImGui::Separator();

            ImGui::TableNextRow();
            ImGui::TableNextColumn(); ImGui::Text("Version:");
            ImGui::TableNextColumn(); ImGui::Text("%s", m_Version);

            ImGui::EndTable();
        }

        ImGui::PopStyleVar();

        ImGui::Spacing();
        ImGui::Separator();
    }
    ImGui::End();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
