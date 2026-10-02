#pragma once

#include <bitset>

#include <GLFW/glfw3.h>

#include "Core/Util.hpp"
#include "Graphics/Camera.hpp"
#include "Window.hpp"
#include "GlfwContext.hpp"
#include "Gui/DebugGui.hpp"
#include "Gui/GuiContext.hpp"

class Game
{
public:
    Game();

    void Run();

private:
    void Render_();
    void ProcessEvents_();
    void ProcessInputs_(float dt);
    
    GlfwContext m_GlfwContext NO_UNIQUE_ADDRESS;

    Window m_Window;
    Camera m_Camera;

    GuiContext m_GuiContext NO_UNIQUE_ADDRESS;
    DebugGui m_Gui;

    std::bitset<GLFW_KEY_LAST> m_Keys;
};
