#pragma once

#include <imgui.h>

#include "Window.hpp"

class Game
{
public:
    Game();
    ~Game();

    void Run();
private:
    void Render_();

    Window m_Window;
};