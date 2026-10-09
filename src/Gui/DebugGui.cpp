#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>

#include "DebugGui.hpp"

DebugGui::DebugGui()
    : io_{ImGui::GetIO()}
    , clear_color_{ImVec4(0.2f, 0.5f, 0.7f, 1.0f)}
{
    vendor_   = glGetString(GL_VENDOR);
    renderer_ = glGetString(GL_RENDERER);
    version_  = glGetString(GL_VERSION);
}

void DebugGui::OnUpdate()
{
    ImGui::Begin("Configurer");
    ImGui::ColorEdit3("clear color", (float*)&clear_color_);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io_.Framerate, io_.Framerate);
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
            ImGui::TableNextColumn(); ImGui::Text("%s", vendor_);

            ImGui::TableNextRow();
            ImGui::TableNextColumn(); ImGui::Text("Renderer:");
            ImGui::TableNextColumn(); ImGui::Text("%s", renderer_);

            ImGui::TableNextRow();
            ImGui::TableNextColumn(); ImGui::Separator();
            ImGui::TableNextColumn(); ImGui::Separator();

            ImGui::TableNextRow();
            ImGui::TableNextColumn(); ImGui::Text("Version:");
            ImGui::TableNextColumn(); ImGui::Text("%s", version_);

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
