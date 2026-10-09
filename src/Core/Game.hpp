#pragma once

#include <bitset>

#include <GLFW/glfw3.h>

#include "Core/Util.hpp"
#include "Graphics/Camera.hpp"
#include "Window.hpp"
#include "Gui/GuiContext.hpp"
#include "Gui/DebugGui.hpp"
#include "Gui/GameplayGui.hpp"

class Game
{
public:
    Game();

    void run();

private:
    void render_();
    void processEvents_();
    void processInputs_(float dt);
    
    Window window_;
    Camera camera_;

    GuiContext guiContext_ NO_UNIQUE_ADDRESS;
    DebugGui debugGui_;
    GameplayGui gameGui_ NO_UNIQUE_ADDRESS;

    std::bitset<GLFW_KEY_LAST> keys_;
};
