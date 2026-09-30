#pragma once

#include <imgui.h>

#include "Graphics/Camera.hpp"
#include "Window.hpp"
#include "GlfwContext.hpp"

class Game
{
public:
    Game();
    ~Game();

    void Run();

private:
    void Render_();
    void ProcessEvents();
    
    NO_UNIQUE_ADDRESS
    GlfwContext m_GlfwContext;

    Window m_Window;
    Camera m_Camera;
};
