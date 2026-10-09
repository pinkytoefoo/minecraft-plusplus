#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>

#include "GameplayGui.hpp"

void GameplayGui::OnUpdate(const Camera& cam)
{
    ImGui::Begin("Gameplay");

    ImGui::Text("Camera pos(x,y,z): %.1f, %.1f, %.1f", cam.getPosition().x, cam.getPosition().y, cam.getPosition().z);
    ImGui::Spacing();

    ImGui::End();
}
