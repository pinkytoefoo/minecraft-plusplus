#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Game.hpp"
#include "Core/GlfwContext.hpp"

int main()
{
    GlfwContext glfwContext;

    Game game;
    game.Run();
}
