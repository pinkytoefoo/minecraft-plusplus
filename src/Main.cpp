#include <iostream>
#include <type_traits>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Game.hpp"
#include "Core/GlfwContext.hpp"
#include "Graphics/IndexBuffer.hpp"

int main()
{
    try
    {
        std::cout << std::boolalpha << std::is_move_constructible_v<IndexBuffer> << '\n';
        GlfwContext glfwContext;

        Game game;
        game.run();
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
