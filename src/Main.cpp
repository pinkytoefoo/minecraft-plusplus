#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Game.hpp"
#include "Core/GlfwContext.hpp"

int main()
{
    try
    {
        GlfwContext glfwContext;

        Game game;
        game.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "exception caught: " << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "unknown exception caught\n";
        return 1;
    }
}