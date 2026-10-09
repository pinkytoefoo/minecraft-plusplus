#pragma once

#include <imgui.h>

#include "Graphics/Camera.hpp"

class GameplayGui
{
public:
    void OnUpdate(const Camera& cam);
};
